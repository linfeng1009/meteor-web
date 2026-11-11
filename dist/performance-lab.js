import {MeteorGame} from './engine.js';
import {turnMouseCamera} from './mouse-look.js';
import {summarizeFrameTrial,assessFrameTrial} from './frame-trial.js';
const canvas=document.querySelector('canvas'),result=document.querySelector('#result');
const buttons=[...document.querySelectorAll('#run,#manual')],lockButton=document.querySelector('#lock');
let game;
let pointerErrors=[];
const sceneStatus=document.querySelector('#scene-status');
let adaptiveUpdate;
const ready=(async()=>{
  buttons.forEach(button=>button.disabled=true);
  game=new MeteorGame(canvas,{onEvent:event=>{
    if(event.type==='pointer-error')pointerErrors.push(event.text);
    if(event.type==='load')sceneStatus.textContent=event.text;
  }});
  await game.ready;game.setSwordStyle('original');game.setMuted(true);game.setQuality('high');
  adaptiveUpdate=game.renderScale.update.bind(game.renderScale);
  await game.menu('sifang');sceneStatus.hidden=true;
  buttons.forEach(button=>button.disabled=false);
})();
ready.catch(error=>{sceneStatus.hidden=false;sceneStatus.textContent='场景载入失败，请刷新重试：'+error.message;result.textContent=error.stack;});

async function trial(mode,settings){
  await game.start({map:settings.map,weapon:'sword',mode:'training'});
  lockButton.disabled=mode!=='manual';
  const cameraTick=game._tickCamera.bind(game),sample=game.frameMeter.sample.bind(game.frameMeter);
  let start=null,previous=null,hidden=false,resized=false,invalidState=false,events=0,lockedEvents=0,pixels=0,lastAttack=-1;
  const initialSize=[canvas.clientWidth,canvas.clientHeight,canvas.width,canvas.height].join(',');
  const frames=[],phases=[],initialAngle=game.cameraAngle,initialPosition=game.hero.root.position.clone();
  let lastAngle=initialAngle,angleTravel=0,turnFrames=0;
  const motion=event=>{events++;pixels+=Math.abs(event.movementX||0)+Math.abs(event.movementY||0);if(document.pointerLockElement===canvas)lockedEvents++;};
  document.addEventListener('mousemove',motion);
  if(mode==='manual')canvas.focus();
  return new Promise(resolve=>{
    game._tickCamera=dt=>{
      if(mode==='orbit'||mode==='combat')turnMouseCamera(game,dt*180,0);
      if(mode==='combat'){
        game.action('forward',true);
        const interval=Math.floor(game.matchElapsed*2);
        if(interval!==lastAttack){game.action('attack',false);game.action('attack',true);lastAttack=interval;}
      }
      cameraTick(dt,{directLook:mode==='orbit'||mode==='combat'});
      invalidState ||= ![game.cameraAngle,game.cameraPitch,...game.camera.position.toArray(),...game.hero.root.position.toArray()].every(Number.isFinite);
      const turn=Math.abs(game.cameraAngle-lastAngle);angleTravel+=turn;if(turn>1e-6)turnFrames++;lastAngle=game.cameraAngle;
    };
    game.frameMeter.sample=(at,timing)=>{
      const stats=sample(at,timing);start??=at;
      hidden ||= document.hidden;
      resized ||= initialSize!==[canvas.clientWidth,canvas.clientHeight,canvas.width,canvas.height].join(',');
      if(at-start>=3000&&previous!==null){frames.push(at-previous);phases.push(timing);}
      previous=at;
      if(at-start>=(mode==='manual'?33000:13000)){
        game.frameMeter.sample=sample;game._tickCamera=cameraTick;
        document.removeEventListener('mousemove',motion);game.releaseInput();game.pause(true);
        lockButton.disabled=true;
        const report={mode,...settings,...summarizeFrameTrial(frames,phases),viewport:[innerWidth,innerHeight],canvas:[canvas.clientWidth,canvas.clientHeight],drawingBuffer:[canvas.width,canvas.height],dpr:game.renderer.getPixelRatio(),drawCalls:game.renderer.info.render.calls,triangles:game.renderer.info.render.triangles,hidden,events,lockedEvents,mousePixels:pixels,angleChange:game.cameraAngle-initialAngle,displacement:game.hero.root.position.distanceTo(initialPosition),runningAtEnd:game.running};
        Object.assign(report,{resized,invalidState,angleTravel,turnFrames,pointerLockSupported:typeof canvas.requestPointerLock==='function',pointerErrors:[...pointerErrors]});
        Object.assign(report,assessFrameTrial(report));
        report.possibleThrottling=report.fps<5&&report.cpuMs<100;
        resolve(report);
      }
      return stats;
    };
  });
}
async function run(modes){
  buttons.forEach(button=>button.disabled=true);
  const settings={map:document.querySelector('#map').value,appearance:document.querySelector('#appearance').value,adaptive:document.querySelector('#adaptive').checked};
  const reports=[];
  try{
    result.textContent='载入中…';await ready;pointerErrors=[];game.setQuality('high');
    await game.setCharacterAppearance(settings.appearance);
    game.renderScale.update=settings.adaptive?adaptiveUpdate:()=>game.renderScale.ratio;
    for(const mode of modes){
      result.textContent=JSON.stringify(reports,null,2)+`\n正在运行 ${mode}，预热3秒+采集${mode==='manual'?30:10}秒…`;
      reports.push(await trial(mode,settings));
      document.querySelector('#summary').textContent=reports.map(r=>`${r.mode}: ${r.fps.toFixed(2)} FPS / P95 ${r.p95Ms.toFixed(1)} ms / >25ms ${r.over25Ms} 帧 / ${r.validForComparison?'采样有效':r.reviewReasons.join('；')}`).join('\n');
      if(reports.at(-1).invalidState)break;
    }
    result.textContent=JSON.stringify(reports,null,2);
  }catch(error){result.textContent=error.stack;game?.dispose();}
  finally{buttons.forEach(button=>button.disabled=false);}
}
document.querySelector('#run').onclick=()=>run(['idle','orbit','combat']);
document.querySelector('#manual').onclick=()=>run(['manual']);
lockButton.onclick=()=>game?.requestMouseLock();
