// @category Meteor
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;import java.util.*;
public class AnalyzeCombat extends GhidraScript {
 public void run() throws Exception {
  File dir=new File(getScriptArgs()[0]);dir.mkdirs();Set<Function> functions=new LinkedHashSet<>();
  Set<String> selected=new HashSet<>(Arrays.asList("mhp"," HP:","meteor.res","Attack","AngAttack","damage","damagevalue","angervalue","angertype","Active Attack","HitAttack"));
  try(PrintWriter out=new PrintWriter(new File(dir,"combat-anchors.txt"),"UTF-8")){
   DataIterator it=currentProgram.getListing().getDefinedData(true);while(it.hasNext()){
    Data d=it.next();Object v=d.getValue();if(!(v instanceof String))continue;String s=(String)v;if(!selected.contains(s)&&!s.contains("BeKill hp")&&!s.contains("Reborn hp"))continue;
    out.println(d.getAddress()+" | "+s);for(Reference r:currentProgram.getReferenceManager().getReferencesTo(d.getAddress())){
     Function f=getFunctionContaining(r.getFromAddress());out.println("  "+r.getFromAddress()+" -> "+(f==null?"no function":f.getEntryPoint()+" "+f.getName()));if(f!=null)functions.add(f);
    }
   }
  }
  DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
  for(Function f:functions){try(PrintWriter out=new PrintWriter(new File(dir,f.getEntryPoint()+"_"+f.getName()+".c"),"UTF-8")){
   out.println("/* Meteor.exe original x86 @ "+f.getEntryPoint()+" */");for(Reference r:currentProgram.getReferenceManager().getReferencesTo(f.getEntryPoint()))out.println("/* Caller: "+r.getFromAddress()+" */");DecompileResults res=decomp.decompileFunction(f,60,monitor);if(res.decompileCompleted())out.print(res.getDecompiledFunction().getC());else out.println(res.getErrorMessage());
  }}decomp.dispose();println("Exported "+functions.size()+" combat anchor functions");
 }
}
