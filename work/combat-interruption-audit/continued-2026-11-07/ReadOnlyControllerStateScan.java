// @category Meteor
// Static instruction scan only. Run with -readOnly -noanalysis.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.symbol.Reference;
import java.io.*;
import java.util.*;

public class ReadOnlyControllerStateScan extends GhidraScript {
  public void run() throws Exception {
    File dir=new File(getScriptArgs()[0]);dir.mkdirs();
    Set<Function> chosen=new LinkedHashSet<>();
    try(PrintWriter out=new PrintWriter(new File(dir,"state-setter-candidates.txt"),"UTF-8")) {
      for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
        monitor.checkCancelled();
        if(!ins.getMnemonicString().equals("CALL")||!ins.toString().contains("0x12c"))continue;
        ArrayList<Instruction> context=new ArrayList<>(); Instruction prev=ins.getPrevious();boolean match=false;
        for(int i=0;prev!=null&&i<10;i++,prev=prev.getPrevious()) {
          if(prev.getMnemonicString().equals("CALL"))break;
          context.add(prev);
          if(prev.getMnemonicString().equals("PUSH")) {
            Scalar val=prev.getScalar(0); if(val!=null&&(val.getUnsignedValue()==7||val.getUnsignedValue()==9))match=true;
          }
        }
        if(!match)continue;
        Function owner=getFunctionContaining(ins.getAddress());if(owner!=null)chosen.add(owner);
        out.println("CANDIDATE "+ins.getAddress()+" owner="+(owner==null?"none":owner.getEntryPoint()));
        Collections.reverse(context);for(Instruction p:context)out.println(p.getAddress()+" "+p);out.println(ins.getAddress()+" "+ins);
      }
    }
    String[] anchors={"004d03f0","004d0500","004d0510","004cde00","004ce250","004cfca0","004f3f50"};
    for(String a:anchors) {Function f=getFunctionAt(toAddr(a));if(f!=null)chosen.add(f);}
    DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
    try(PrintWriter index=new PrintWriter(new File(dir,"functions.tsv"),"UTF-8")) {
      for(Function f:chosen) {
        monitor.checkCancelled();String stem=f.getEntryPoint()+"_"+f.getName();index.println(f.getEntryPoint()+"\t"+f.getName()+"\t"+f.getBody().getNumAddresses());
        try(PrintWriter out=new PrintWriter(new File(dir,stem+".c"),"UTF-8")) {
          out.println("/* Original Meteor.exe static export; sample not executed. */");
          for(Reference r:currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint()))out.println("/* XREF "+r.getFromAddress()+" "+r.getReferenceType()+" */");
          DecompileResults d=decomp.decompileFunction(f,60,monitor);if(d.decompileCompleted())out.print(d.getDecompiledFunction().getC());else out.println(d.getErrorMessage());
        }
        try(PrintWriter out=new PrintWriter(new File(dir,stem+".asm"),"UTF-8")){for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins);}
      }
    }
    decomp.dispose();println("Exported "+chosen.size()+" state setter candidate functions; object identity must be checked manually.");
  }
}
