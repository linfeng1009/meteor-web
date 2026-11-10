// @category Meteor
// Source query only; use -readOnly -noanalysis, no program mutation.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ReadOnlyItemConsumerTrace extends GhidraScript {
  public void run() throws Exception {
    File dir = new File(getScriptArgs()[0]); dir.mkdirs();
    LinkedHashSet<Function> functions = new LinkedHashSet<>();
    try(PrintWriter out=new PrintWriter(new File(dir,"references.txt"),"UTF-8")) {
      for(String value:new String[]{"004d4d30","004d4e30","004d5020","004d59d0","004d5d30","004d5d70","004d5de0","004d5e30","004d4b40","004d4c00","004b24e0","0048aeb0","004abaa0","004abf50"}) {
        Address address=toAddr(value);Function f=getFunctionContaining(address);if(f!=null)functions.add(f);
        out.println("ADDRESS "+address+" owner="+(f==null?"none":f.getEntryPoint()));
        for(Reference ref:currentProgram.getReferenceManager().getReferencesTo(address))out.println(ref.getFromAddress()+" "+ref.getReferenceType()+" owner="+getFunctionContaining(ref.getFromAddress()));
      }
      for(String value:new String[]{"005a9488","005a84ac","005a9cf4"}) {
        Address address=toAddr(value);out.println("DATA "+address);
        int count=value.equals("005a9488")?24:value.equals("005a9cf4")?80:2;
        for(int i=0;i<count;i++) {
          int data=currentProgram.getMemory().getInt(address.add(i*4));out.printf("%s %08x float=%s%n",address.add(i*4),data,Float.toString(Float.intBitsToFloat(data)));
          if(value.equals("005a9488")) {Function f=getFunctionAt(toAddr(Integer.toUnsignedLong(data)));if(f!=null)functions.add(f);}
        }
      }
    }
    try(PrintWriter out=new PrintWriter(new File(dir,"stat-pointer-update-candidates.txt"),"UTF-8")) {
      for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
        if(!(ins.toString().contains("+ 0x88]") || ins.toString().contains("+ 0x70]")))continue;
        Instruction cursor=ins;boolean update=false;
        for(int i=0;i<12 && cursor!=null;i++,cursor=cursor.getNext()) {
          if(cursor.getMnemonicString().equalsIgnoreCase("CALL") && cursor.toString().contains("+ 0x4]"))update=true;
        }
        if(!update)continue;
        Function f=getFunctionContaining(ins.getAddress());if(f!=null)functions.add(f);
        out.println("CANDIDATE "+ins.getAddress()+" owner="+(f==null?"none":f.getEntryPoint()));
        cursor=ins;for(int i=0;i<16 && cursor!=null;i++,cursor=cursor.getNext())out.println(cursor.getAddress()+" "+cursor);
      }
    }
    DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
    for(Function f:functions) {
      monitor.checkCancelled();String stem=f.getEntryPoint()+"_"+f.getName();
      try(PrintWriter out=new PrintWriter(new File(dir,stem+".c"),"UTF-8")) {
        out.println("/* Original Meteor.exe static read-only export; sample not executed. */");
        DecompileResults result=decomp.decompileFunction(f,60,monitor);out.print(result.decompileCompleted()?result.getDecompiledFunction().getC():result.getErrorMessage());
      }
      try(PrintWriter out=new PrintWriter(new File(dir,stem+".asm"),"UTF-8")) {for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins);}
    }
    decomp.dispose();println("Read-only exported "+functions.size()+" source functions");
  }
}
