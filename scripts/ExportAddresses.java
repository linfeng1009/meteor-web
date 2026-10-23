// @category Meteor
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class ExportAddresses extends GhidraScript {
 public void run() throws Exception {
  String[] args=getScriptArgs();File dir=new File(args[0]);dir.mkdirs();
  DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
  for(int i=1;i<args.length;i++){
   Function f=getFunctionContaining(toAddr(args[i]));if(f==null){println("No function: "+args[i]);continue;}
   try(PrintWriter out=new PrintWriter(new File(dir,f.getEntryPoint()+"_"+f.getName()+".c"),"UTF-8")){
    out.println("/* Meteor.exe original x86 @ "+f.getEntryPoint()+" */");
    for(Reference ref:currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint()))out.println("/* Caller: "+ref.getFromAddress()+" */");
    DecompileResults result=decomp.decompileFunction(f,60,monitor);
    if(result.decompileCompleted())out.print(result.getDecompiledFunction().getC());else out.println("/* "+result.getErrorMessage()+" */");
   }
  }decomp.dispose();
 }
}
