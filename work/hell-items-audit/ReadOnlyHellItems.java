// @category Meteor
// Read-only listing/decompilation query. Never modifies the program or sample.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.io.*;
import java.util.*;
public class ReadOnlyHellItems extends GhidraScript {
  public void run() throws Exception {
    File dir = new File(getScriptArgs()[0]); dir.mkdirs();
    Set<Function> candidates = new LinkedHashSet<>();
    try (PrintWriter out = new PrintWriter(new File(dir, "stat10-call-sites.txt"), "UTF-8")) {
      InstructionIterator it = currentProgram.getListing().getInstructions(true);
      while (it.hasNext()) {
        Instruction ins = it.next(); boolean ten = false;
        for (int i=0;i<ins.getNumOperands();i++) for (Object operand:ins.getOpObjects(i))
          if (operand instanceof Scalar && ((Scalar)operand).getUnsignedValue()==10) ten=true;
        if (!ten || !ins.getMnemonicString().equals("PUSH")) continue;
        Instruction next=ins; boolean statCall=false;
        for (int i=0;i<12 && next!=null;i++,next=next.getNext()) {
          String text=next.toString();
          if (next.getMnemonicString().equals("CALL") && (text.contains("0x34]") || text.contains("0x30]"))) statCall=true;
        }
        Function owner=getFunctionContaining(ins.getAddress());
        out.println("PUSH10 "+ins.getAddress()+" owner="+(owner==null?"none":owner.getEntryPoint()+" "+owner.getName())+" candidate="+statCall);
        next=ins; for(int i=0;i<14 && next!=null;i++,next=next.getNext())out.println(next.getAddress()+" "+next);
        if(statCall && owner!=null)candidates.add(owner);
      }
    }
    for(String anchor:new String[]{"004aa29a","00494ecf"}) {
      Function f=getFunctionContaining(toAddr(anchor)); if(f!=null)candidates.add(f);
    }
    DecompInterface decomp=new DecompInterface(); decomp.openProgram(currentProgram);
    for(Function f:candidates) {
      try(PrintWriter out=new PrintWriter(new File(dir,f.getEntryPoint()+"_"+f.getName()+".c"),"UTF-8")) {
        out.println("/* Original Meteor.exe static read-only export; sample not executed. */");
        DecompileResults result=decomp.decompileFunction(f,60,monitor);
        out.println(result.decompileCompleted()?result.getDecompiledFunction().getC():result.getErrorMessage());
      }
      try(PrintWriter out=new PrintWriter(new File(dir,f.getEntryPoint()+"_"+f.getName()+".asm"),"UTF-8")) {
        InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);
        while(it.hasNext()){Instruction ins=it.next();out.println(ins.getAddress()+" "+ins);}
      }
    }
    decomp.dispose(); println("Exported "+candidates.size()+" original candidate functions");
  }
}
