// @category Meteor
// Narrow read-only search for the animation movement-vector producer.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.io.*;
import java.util.*;
public class ReadOnlyMotionOwners extends GhidraScript {
  public void run() throws Exception {
    File dir=new File(getScriptArgs()[0]);dir.mkdirs();Set<Function> owners=new LinkedHashSet<>();
    try(PrintWriter out=new PrintWriter(new File(dir,"field-accesses.txt"),"UTF-8")) {
      for(Instruction ins:currentProgram.getListing().getInstructions(toAddr("00550000"),true)) {
        if(ins.getAddress().compareTo(toAddr("00560000"))>=0)break;
        boolean match=false;
        for(int i=0;i<ins.getNumOperands();i++)for(Object o:ins.getOpObjects(i))if(o instanceof Scalar&&Arrays.asList(0x304L,0x300L,0x2f8L,0x2fcL).contains(((Scalar)o).getUnsignedValue()))match=true;
        if(match){Function owner=getFunctionContaining(ins.getAddress());out.println(ins.getAddress()+" "+ins+" owner="+(owner==null?"none":owner.getEntryPoint()));if(owner!=null)owners.add(owner);}
      }
    }
    DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
    for(Function f:owners) {
      try(PrintWriter out=new PrintWriter(new File(dir,f.getEntryPoint()+"_"+f.getName()+".c"),"UTF-8")) {
        out.println("/* Original Meteor.exe read-only motion producer export; sample not executed. */");
        DecompileResults r=decomp.decompileFunction(f,60,monitor);out.println(r.decompileCompleted()?r.getDecompiledFunction().getC():r.getErrorMessage());
      }
      try(PrintWriter out=new PrintWriter(new File(dir,f.getEntryPoint()+"_"+f.getName()+".asm"),"UTF-8")) {
        for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins);
      }
    }
    decomp.dispose();println("Read-only motion owners: "+owners.size());
  }
}
