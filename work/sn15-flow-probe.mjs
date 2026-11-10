import { nativeFiles, nativeMission, tick, attackWhenReady, v } from '../tests/helpers/native-mission-fixture.mjs';
const restore = nativeFiles(), f = await nativeMission('sn15'), {game,host} = f;
try {
  for(let i=0;i<340;i++)tick(game,.1,{enemies:false});
  const vip=host.findActor('萧安'), start=game.hero.root.position.clone();
  game._placeFighter(game.hero,{position:vip.root.position.clone().add(v(0,0,-1.1))});game.locked=vip;
  for(let i=0;i<20000 && vip.hp>=1800 && game.running;i++){
    if(!game.hero.combat.busy)game._placeFighter(game.hero,{position:vip.root.position.clone().add(v(0,0,-1.1))});
    attackWhenReady(game);tick(game,1/30,{enemies:false});
  }
  console.log('DAMAGED',JSON.stringify({time:host.clock,hp:vip.hp,hero:game.hero.hp,hits:game.contactHits,trg7:host.levelVm.getGlobal('trg7'),guard:vip.guard,diagnostics:host.diagnostics}));
  if(process.argv.includes('escape')){
    game._placeFighter(game.hero,{position:start});game.locked=null;
    const phases=[];
    for(let i=0;i<6000 && game.running;i++){
      tick(game,1/30,{enemies:false});game._updateFighter(vip,1/30);
      if(phases.at(-1)?.phase!==host.levelVm.getGlobal('trg7'))phases.push({phase:host.levelVm.getGlobal('trg7'),time:host.clock,position:vip.root.position.toArray(),intent:vip.scriptIntent});
    }
    console.log('ESCAPE',JSON.stringify({result:host.completed,hp:vip.hp,dead:vip.dead,removed:vip.scriptRemoved,position:vip.root.position.toArray(),path:vip.scriptPath,phases,diagnostics:host.diagnostics}));
  }else{
    for(let i=0;i<20000 && !vip.dead && game.running;i++){
      if(!game.hero.combat.busy)game._placeFighter(game.hero,{position:vip.root.position.clone().add(v(0,0,-1.1))});
      attackWhenReady(game);tick(game,1/30,{enemies:false});
    }
    for(let i=0;i<60&&game.running;i++)tick(game,1/30,{enemies:false});
    console.log('VICTORY',JSON.stringify({result:host.completed,hp:vip.hp,kills:game.kills,damage:game.totalDamage,diagnostics:host.diagnostics}));
  }
}finally{f.dispose();restore();}
