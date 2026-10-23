// @category Meteor
// Signatures are recovered from x86 ECX + stack arguments and RET n, not guessed names.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.data.*;
import ghidra.program.model.pcode.HighFunctionDBUtil;
import ghidra.app.decompiler.*;
import java.io.*;
public class AnnotateCombatCalls extends GhidraScript {
 void signature(String addr,String name,DataType ret,DataType... types)throws Exception{
  Function f=getFunctionContaining(toAddr(addr)); if(f==null)throw new Exception("No owner "+addr);
  FunctionDefinitionDataType sig=new FunctionDefinitionDataType(name);sig.setCallingConvention("__thiscall");sig.setReturnType(ret);
  ParameterDefinition[] ps=new ParameterDefinition[types.length];for(int i=0;i<types.length;i++)ps[i]=new ParameterDefinitionImpl("arg"+i,types[i],null);sig.setArguments(ps);
  HighFunctionDBUtil.writeOverride(f,toAddr(addr),sig);
 }
 public void run()throws Exception{
  DataType I=IntegerDataType.dataType,P=new PointerDataType(VoidDataType.dataType),F=FloatDataType.dataType;
  for(String a:new String[]{"004af8bc","004af921","004d5e47","004d6281","004d61a7"})signature(a,"statGet",I,P,I,P);
  for(String a:new String[]{"004af879","004af95f","004d5fa0"})signature(a,"statAdd",I,P,I,I,P);
  signature("004af83d","poseMinusDefense",I,P,I,P);
  signature("004d5f7d","poseMinusDefense",I,P,I,P);
  signature("004af90e","applyPoseDamage",VoidDataType.dataType,P,I,P,F);
  signature("004d6198","poseAttack",I,P,I);
  signature("004afa48","poseExtraItem",I,P,I,I,P);
  DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
  for(String a:new String[]{"004af630","004d5e30","004d5f70","004d6190","004d61c0"}){
   Function f=getFunctionAt(toAddr(a)); DecompileResults r=d.decompileFunction(f,60,monitor);
   try(PrintWriter out=new PrintWriter(new File(getScriptArgs()[0],a+"_FUN_"+a+".c"),"UTF-8")){
    out.println("/* Original Meteor.exe @ "+a+"; stat virtual-call signatures annotated from x86 calling convention */");
    if(r.decompileCompleted())out.print(r.getDecompiledFunction().getC());
   }
  }d.dispose();
 }
}
