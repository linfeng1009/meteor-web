// @category Meteor
// Read-only instruction queries and original function exports.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.io.*;
import java.util.*;
public class ReadOnlyDodgeScan extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs(); File dir=new File(args[0]);dir.mkdirs();Set<Function> funcs=new LinkedHashSet<>();Set<Long> values=new HashSet<>();
  for(int i=1;i<args.length;i++)values.add(Long.parseLong(args[i],16));
  try(PrintWriter out=new PrintWriter(new File(dir,"candidates.txt"),"UTF-8")) {
   for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
    if(ins.getAddress().getOffset()<0x004d0000L || ins.getAddress().getOffset()>0x004dffffL)continue;
    boolean match=false;
    for(int i=0;i<ins.getNumOperands();i++)for(Object o:ins.getOpObjects(i))if(o instanceof Scalar && values.contains(((Scalar)o).getUnsignedValue()))match=true;
    if(!match)continue;
    if(args[1].equals("2") && !(ins.toString().contains("word ptr [") && ins.toString().contains(" + 0x2]")))continue;
    if(args.length>1 && args[1].equals("114") && (ins.getAddress().getOffset()<0x004d0000L || ins.getAddress().getOffset()>0x005049ffL))continue;
    Function f=getFunctionContaining(ins.getAddress()); out.println(ins.getAddress()+" "+ins+" owner="+(f==null?"none":f.getEntryPoint()));
    if(f!=null)funcs.add(f);
   }
  }
  DecompInterface dec=new DecompInterface();dec.openProgram(currentProgram);
  for(Function f:funcs) {
   String stem=f.getEntryPoint()+"_"+f.getName();
   try(PrintWriter out=new PrintWriter(new File(dir,stem+".c"),"UTF-8")) {
    out.println("/* Original Meteor.exe read-only export. Sample not executed. */");DecompileResults r=dec.decompileFunction(f,60,monitor);out.print(r.decompileCompleted()?r.getDecompiledFunction().getC():r.getErrorMessage());
   }
   try(PrintWriter out=new PrintWriter(new File(dir,stem+".asm"),"UTF-8")) {for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins);}
  }
  dec.dispose();println("Read-only exported "+funcs.size()+" field consumers");
 }
}
