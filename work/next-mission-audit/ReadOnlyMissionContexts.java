// @category Meteor
// Export existing instructions only. Invoke with -readOnly -noanalysis.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
public class ReadOnlyMissionContexts extends GhidraScript {
  public void run() throws Exception {
    File dir = new File(getScriptArgs()[0]); dir.mkdirs();
    try (PrintWriter out = new PrintWriter(new File(dir,"contexts.asm"),"UTF-8")) {
      for (Reference ref:currentProgram.getReferenceManager().getReferencesTo(toAddr("0056cb70"))) {
        out.println("CALLBACK SETTER " + ref);
        Address start=ref.getFromAddress().subtract(160), end=ref.getFromAddress().add(50);
        for(Instruction ins:currentProgram.getListing().getInstructions(start,true)) {
          if(ins.getAddress().compareTo(end)>0)break;
          out.println(ins.getAddress()+" "+ins);
        }
      }
      out.println("BYTE WRITES TO OFFSET60");
      for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
        String s=ins.toString();
        if((s.startsWith("MOV byte ptr [") && s.contains("+ 0x210]")) || (s.contains("0x578]") && !s.contains("ESP"))) {
          out.println("CANDIDATE " + ins.getAddress()+" "+s);
          for(Instruction context:currentProgram.getListing().getInstructions(ins.getAddress().subtract(48),true)) {
            if(context.getAddress().compareTo(ins.getAddress().add(48))>0)break;
            out.println(context.getAddress()+" "+context);
          }
        }
      }
    }
  }
}
