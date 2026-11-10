// @category Meteor
// Static read-only instruction-owner scan. Original sample is never executed.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import java.io.*;
import java.util.*;
public class ReadOnlyKnuckleStateTrace extends GhidraScript {
 public void run() throws Exception {
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();Set<Long> ids=new HashSet<>(Arrays.asList(412L,413L,416L,421L,422L,423L,424L,425L,426L,489L));Set<Function> fs=new LinkedHashSet<>();
  try(PrintWriter out=new PrintWriter(new File(dir,"pose-immediates.txt"),"UTF-8")) {
   for(Instruction ins:currentProgram.getListing().getInstructions(true)) {
    if(!Arrays.asList("CMP","PUSH").contains(ins.getMnemonicString().toUpperCase()))continue;
    boolean found=false;for(int i=0;i<ins.getNumOperands();i++)for(Object obj:ins.getOpObjects(i))if(obj instanceof Scalar&&ids.contains(((Scalar)obj).getUnsignedValue()))found=true;
    if(found){Function f=getFunctionContaining(ins.getAddress());out.println(ins.getAddress()+" "+ins+" owner="+(f==null?"none":f.getEntryPoint()));if(f!=null)fs.add(f);}
   }
  }
  DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
  for(Function f:fs){String stem=f.getEntryPoint()+"_"+f.getName();try(PrintWriter out=new PrintWriter(new File(dir,stem+".c"),"UTF-8")){out.println("/* Original Meteor.exe static export @ "+f.getEntryPoint()+"; original sample not executed. */");DecompileResults r=d.decompileFunction(f,60,monitor);if(r.decompileCompleted())out.print(r.getDecompiledFunction().getC());else out.println(r.getErrorMessage());}}
  d.dispose();println("Read-only knuckle scan exported "+fs.size()+" owner functions to "+dir);
 }
}
