import http from 'node:http';
import { readFile } from 'node:fs/promises';
import { resolve, extname, sep } from 'node:path';
import { fileURLToPath } from 'node:url';
const root = fileURLToPath(new URL('./dist/', import.meta.url));
const types={'.html':'text/html; charset=utf-8','.js':'text/javascript; charset=utf-8','.css':'text/css; charset=utf-8','.json':'application/json; charset=utf-8','.svg':'image/svg+xml','.png':'image/png','.jpg':'image/jpeg','.jpeg':'image/jpeg','.webp':'image/webp','.woff2':'font/woff2','.bmp':'image/bmp','.gmc':'text/plain; charset=utf-8','.md':'text/plain; charset=utf-8','.mp3':'audio/mpeg','.wav':'audio/wav'};
const handleRequest=async(req,res)=>{
  try{
    const url=new URL(req.url,'http://localhost');
    const target=resolve(root,'.'+decodeURIComponent(url.pathname==='/'?'/index.html':url.pathname));
    if(!target.startsWith(root.endsWith(sep)?root:root+sep)) {res.writeHead(403);res.end();return;}
    const data=await readFile(target);res.writeHead(200,{'Content-Type':types[extname(target)]||'application/octet-stream','Cache-Control':'no-cache','X-Content-Type-Options':'nosniff'});res.end(data);
  }catch{res.writeHead(404,{'Content-Type':'text/plain; charset=utf-8'});res.end('Not found');}
};
const port=Number(process.env.PORT)||4173;
const hosts=[process.env.HOST||'127.0.0.1',process.env.LAN_HOST].filter((host,index,list)=>host&&list.indexOf(host)===index);
function listenHost(index=0){
  if(index>=hosts.length)return;
  const host=hosts[index],server=http.createServer(handleRequest);
  server.on('error',error=>{
    if(index>0){
      console.warn(`局域网地址 ${host}:${port} 无法监听（${error.code || error.message}），本地服务不受影响。`);
    }else{
      console.error(`本地服务无法启动：${host}:${port}（${error.code || error.message}）。请检查端口是否被占用。`);
      process.exitCode=1;
    }
  });
  server.listen(port,host,()=>{
    console.log(`流星蝴蝶剑 Web · http://${host}:${server.address().port}/`);
    listenHost(index+1);
  });
}
listenHost();
