// Read-only Ghidra post-analysis export of file parsers, pose data, and xrefs.
// @category Meteor
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class ExportMeteor extends GhidraScript {
    public void run() throws Exception {
        String[] args=getScriptArgs();
        File directory=new File(args[0]);directory.mkdirs();
        DecompInterface decompiler=new DecompInterface();
        decompiler.openProgram(currentProgram);
        LinkedHashMap<Function,ArrayList<String>> found=new LinkedHashMap<>();
        try(PrintWriter out=new PrintWriter(new File(directory,"xref-index.txt"),"UTF-8")){
            out.println("Program: "+currentProgram.getName());
            out.println("Language: "+currentProgram.getLanguageID());
            DataIterator data=currentProgram.getListing().getDefinedData(true);
            while(data.hasNext()&&!monitor.isCancelled()){
                Data item=data.next();Object value=item.getValue();
                if(!(value instanceof String))continue;
                String text=(String)value;
                if(!text.toLowerCase().matches(".*(\\.skc|\\.bnc|\\.amb|character\\.act|targetmove|targetvalue|defensemove|nextpose|attackvalue|frameweight|pose structure|posefield|load pose fail).*"))continue;
                ReferenceIterator refs=currentProgram.getReferenceManager().getReferencesTo(item.getAddress());
                while(refs.hasNext()){
                    Reference ref=refs.next();
                    Function f=currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress());
                    out.println(item.getAddress()+" | "+text+" | "+ref.getFromAddress()+" | "+(f==null?"no function":f.getEntryPoint()+" "+f.getName()));
                    if(f!=null)found.computeIfAbsent(f,k->new ArrayList<>()).add(text);
                }
            }
            if(args.length>1){
                for(String line:java.nio.file.Files.readAllLines(new File(args[1]).toPath())){
                    String[] parts=line.split("\\t",2);if(parts.length<2)continue;
                    Address anchor=toAddr(parts[0]);
                    for(Reference ref:currentProgram.getReferenceManager().getReferencesTo(anchor)){
                        Function f=currentProgram.getFunctionManager().getFunctionContaining(ref.getFromAddress());
                        out.println(anchor+" | "+parts[1]+" | "+ref.getFromAddress()+" | "+(f==null?"no function":f.getEntryPoint()+" "+f.getName()));
                        if(f!=null)found.computeIfAbsent(f,k->new ArrayList<>()).add(parts[1]);
                    }
                }
            }
        }
        try(PrintWriter out=new PrintWriter(new File(directory,"function-index.tsv"),"UTF-8")){
            FunctionIterator functions=currentProgram.getFunctionManager().getFunctions(true);
            while(functions.hasNext()){Function f=functions.next();out.println(f.getEntryPoint()+"\t"+f.getName()+"\t"+f.getBody().getNumAddresses());}
        }
        int count=0;
        for(Map.Entry<Function,ArrayList<String>> entry:found.entrySet()){
            if(monitor.isCancelled())break;
            Function function=entry.getKey();
            DecompileResults result=decompiler.decompileFunction(function,45,monitor);
            File output=new File(directory,function.getEntryPoint()+"_"+function.getName()+".c");
            try(PrintWriter out=new PrintWriter(output,"UTF-8")){
                out.println("/* Decompiled from user's Meteor.exe; address: "+function.getEntryPoint()+" */");
                out.println("/* String anchors: "+entry.getValue()+" */");
                if(result.decompileCompleted())out.print(result.getDecompiledFunction().getC());
                else out.println("/* DECOMPILE FAILED: "+result.getErrorMessage()+" */");
            }
            count++;
        }
        decompiler.dispose();println("Exported "+count+" anchored functions into "+directory.getAbsolutePath());
    }
}
