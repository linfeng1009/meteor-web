// @category Meteor
// Read-only, narrowly scoped immediate-151 jump entry search.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.io.*;
import java.util.*;
public class ReadOnlyJumpTrace extends GhidraScript {
 public void run() throws Exception {
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();Set<Function> owners=new LinkedHashSet<>();
  try(PrintWriter out=new PrintWriter(new File(dir,"jump-anchors.txt"),"UTF-8")){
   for(Instruction ins:currentProgram.getListing().getInstructions(true)){
    long a=ins.getAddress().getOffset();if(a<0x004a8000L||a>0x004f5000L||!Arrays.asList("PUSH","CMP","MOV").contains(ins.getMnemonicString()))continue;
    boolean hit=false;for(int i=0;i<ins.getNumOperands();i++)for(Object o:ins.getOpObjects(i))if(o instanceof Scalar&&((Scalar)o).getUnsignedValue()==151)hit=true;
    if(hit){Function f=getFunctionContaining(ins.getAddress());out.println(ins.getAddress()+" "+ins+" owner="+(f==null?"none":f.getEntryPoint()));if(f!=null)owners.add(f);}
   }
  }
  DecompInterface dc=new DecompInterface();dc.openProgram(currentProgram);
  for(Function f:owners){monitor.checkCancelled();String stem=f.getEntryPoint()+"_"+f.getName();
   try(PrintWriter out=new PrintWriter(new File(dir,stem+".c"),"UTF-8")){var r=dc.decompileFunction(f,60,monitor);out.println("/* Original Meteor.exe static; sample not executed. */");if(r.decompileCompleted())out.print(r.getDecompiledFunction().getC());}
   try(PrintWriter out=new PrintWriter(new File(dir,stem+".asm"),"UTF-8")){for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins);}
  }dc.dispose();println("Read-only jump owners: "+owners.size());
 }
}
