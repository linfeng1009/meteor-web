// @category Meteor
// Read-only source query; no sample execution and no program mutation.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;
public class ReadOnlyItemSchedulerTrace extends GhidraScript {
 public void run() throws Exception {
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();Set<Function> functions=new LinkedHashSet<>();
  try(PrintWriter out=new PrintWriter(new File(dir,"candidates.txt"),"UTF-8")) {
   for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
    long address=ins.getAddress().getOffset();String s=ins.toString();
    boolean candidate=(address>=0x00480000L && address<0x004c0000L && ins.getMnemonicString().equalsIgnoreCase("CALL") && s.contains("+ 0xb4]")) || s.contains("+ 0x2080]");
    if(!candidate)continue;Function f=getFunctionContaining(ins.getAddress());if(f!=null)functions.add(f);
    out.println("ANCHOR "+ins.getAddress()+" owner="+(f==null?"none":f.getEntryPoint()));Instruction c=ins;
    for(int i=0;i<12 && c.getPrevious()!=null;i++)c=c.getPrevious();
    for(int i=0;i<27 && c!=null;i++,c=c.getNext())out.println(c.getAddress()+" "+c);
   }
  }
  for(String addr:new String[]{"004b24c0","004abe80","005498c0","005499a0","00549a90","00549b00"}){Function f=getFunctionContaining(toAddr(addr));if(f!=null)functions.add(f);}
  DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
  try(PrintWriter refs=new PrintWriter(new File(dir,"references.txt"),"UTF-8")) {
   for(Function f:functions) {
    refs.println("FUNCTION "+f.getEntryPoint());for(Reference r:currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint()))refs.println(r.getFromAddress()+" "+r.getReferenceType()+" owner="+getFunctionContaining(r.getFromAddress()));
    String stem=f.getEntryPoint()+"_"+f.getName();
    try(PrintWriter out=new PrintWriter(new File(dir,stem+".c"),"UTF-8")){out.println("/* Original Meteor.exe static read-only source export; not executed. */");DecompileResults result=d.decompileFunction(f,60,monitor);out.print(result.decompileCompleted()?result.getDecompiledFunction().getC():result.getErrorMessage());}
    try(PrintWriter out=new PrintWriter(new File(dir,stem+".asm"),"UTF-8")){for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins);}
   }
  }
  d.dispose();println("Exported "+functions.size()+" source scheduler functions");
 }
}
