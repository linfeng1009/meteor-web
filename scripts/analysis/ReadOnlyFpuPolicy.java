// @category Meteor
// Inspect FPU policy writers in an existing read-only Ghidra project.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.Reference;
import java.io.*;
import java.util.*;

public class ReadOnlyFpuPolicy extends GhidraScript {
  public void run() throws Exception {
    File dir = new File(getScriptArgs()[0]); dir.mkdirs();
    Set<Function> owners = new LinkedHashSet<>();
    try (PrintWriter out = new PrintWriter(new File(dir, "fpu-writers.tsv"), "UTF-8")) {
      for (Instruction ins : currentProgram.getListing().getInstructions(true)) {
        if (!Arrays.asList("FLDCW", "FNINIT", "FINIT", "LDMXCSR", "FXRSTOR", "FRSTOR").contains(ins.getMnemonicString().toUpperCase())) continue;
        Function owner = getFunctionContaining(ins.getAddress());
        out.println(ins.getAddress() + "\t" + ins + "\t" + (owner == null ? "none" : owner.getEntryPoint()));
        if (owner != null) owners.add(owner);
      }
    }
    DecompInterface decompiler = new DecompInterface(); decompiler.openProgram(currentProgram);
    try {
      for (Function f : owners) {
        monitor.checkCancelled(); String stem = f.getEntryPoint() + "_" + f.getName();
        try (PrintWriter out = new PrintWriter(new File(dir, stem + ".c"), "UTF-8")) {
          out.println("/* Original Meteor.exe read-only FPU-policy export @ " + f.getEntryPoint() + "; native sample not executed. */");
          for (Reference ref : currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint())) out.println("/* XREF " + ref.getFromAddress() + " " + ref.getReferenceType() + " */");
          DecompileResults result = decompiler.decompileFunction(f, 45, monitor);
          out.print(result.decompileCompleted() ? result.getDecompiledFunction().getC() : result.getErrorMessage());
        }
        try (PrintWriter out = new PrintWriter(new File(dir, stem + ".asm"), "UTF-8")) {
          for (Instruction ins : currentProgram.getListing().getInstructions(f.getBody(), true)) out.println(ins.getAddress() + " " + ins);
        }
      }
    } finally { decompiler.dispose(); }
    println("Read-only FPU policy owners: " + owners.size());
  }
}
