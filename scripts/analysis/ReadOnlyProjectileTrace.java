// @category Meteor
// Read-only export: use with analyzeHeadless -readOnly -noanalysis.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.scalar.Scalar;
import java.io.*;
import java.util.*;

public class ReadOnlyProjectileTrace extends GhidraScript {
  public void run() throws Exception {
    String[] args = getScriptArgs(); File dir = new File(args[0]); dir.mkdirs();
    LinkedHashSet<Function> functions = new LinkedHashSet<>();
    try (PrintWriter out = new PrintWriter(new File(dir, "references.txt"), "UTF-8")) {
      for (int i = 1; i < args.length; i++) {
        if (args[i].equals("scan-dart")) {
          try(PrintWriter scan = new PrintWriter(new File(dir,"dart-immediates.txt"),"UTF-8")) {
            for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
              if(!Arrays.asList("CMP","PUSH","SUB").contains(ins.getMnemonicString().toUpperCase()))continue;
              boolean found=false;
              for(int operand=0;operand<ins.getNumOperands();operand++)for(Object obj:ins.getOpObjects(operand))if(obj instanceof Scalar) { long value=((Scalar)obj).getUnsignedValue(); if(value==200 || value==202)found=true; }
              if(found) {Function owner=getFunctionContaining(ins.getAddress()); scan.println(ins.getAddress()+" "+ins+" owner="+(owner==null?"none":owner.getEntryPoint()));if(owner!=null)functions.add(owner);}
            }
          }
          continue;
        }
        Address address = toAddr(args[i]); Function f = getFunctionAt(address);
        if (f == null && currentProgram.getMemory().getBlock(address).isExecute()) {
          f=getFunctionContaining(address);
          if(f==null) { disassemble(address); f=createFunction(address,null); }
        }
        if (f != null) functions.add(f);
        out.println("ADDRESS " + address + " " + getDataAt(address));
        for (Reference ref : currentProgram.getReferenceManager().getReferencesTo(address)) {
          Function owner = getFunctionContaining(ref.getFromAddress());
          out.println(ref.getFromAddress() + " " + ref.getReferenceType() + " owner=" + (owner == null ? "none" : owner.getEntryPoint() + " " + owner.getName()));
          if (f == null && owner != null) functions.add(owner);
        }
        byte[] bytes = new byte[64];
        try { currentProgram.getMemory().getBytes(address, bytes); out.print("DATA32"); for (int j=0;j<64;j+=4) { int v=(bytes[j]&255)|((bytes[j+1]&255)<<8)|((bytes[j+2]&255)<<16)|(bytes[j+3]<<24); out.printf(" %08x(%s)",v,Float.toString(Float.intBitsToFloat(v))); } out.println(); } catch(Exception ignored) {}
      }
    }
    DecompInterface decomp = new DecompInterface(); decomp.openProgram(currentProgram);
    try (PrintWriter index = new PrintWriter(new File(dir,"functions.tsv"),"UTF-8")) {
      for (Function f : functions) {
        monitor.checkCancelled(); String stem=f.getEntryPoint()+"_"+f.getName();
        index.println(f.getEntryPoint()+"\t"+f.getName()+"\t"+f.getBody().getNumAddresses());
        try (PrintWriter out = new PrintWriter(new File(dir,stem+".c"),"UTF-8")) {
          out.println("/* Original Meteor.exe static export @ "+f.getEntryPoint()+"; original sample not executed. */");
          for (Reference ref:currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint())) out.println("/* XREF "+ref.getFromAddress()+" "+ref.getReferenceType()+" */");
          DecompileResults r=decomp.decompileFunction(f,60,monitor);
          if(r.decompileCompleted())out.print(r.getDecompiledFunction().getC()); else out.println("/* "+r.getErrorMessage()+" */");
        }
        try(PrintWriter out=new PrintWriter(new File(dir,stem+".asm"),"UTF-8")) {
          for(Instruction ins:currentProgram.getListing().getInstructions(f.getBody(),true))out.println(ins.getAddress()+" "+ins.toString());
        }
      }
    }
    decomp.dispose(); println("Read-only exported "+functions.size()+" functions to "+dir);
  }
}
