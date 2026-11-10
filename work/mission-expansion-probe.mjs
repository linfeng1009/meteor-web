// Development probe: original CPU scene/actors, no renderer/audio/image decode.
import { nativeFiles, nativeMission, tick } from '../tests/helpers/native-mission-fixture.mjs';
const restore = nativeFiles();
try {
  for (const mapId of ['sn09', 'sn15']) {
    const f = await nativeMission(mapId), {game,host} = f;
    console.log(mapId, JSON.stringify({hero:[game.hero.hp,game.hero.weapon,game.hero.root.position.toArray()],
      actors:game.enemies.map(a=>[a.name,a.hp,a.weapon,a.root.position.toArray()]), warnings:game.currentMap.props.warnings,
      floors:[...game.currentMap.props.instances.values()].filter(i=>/D_sn09f/.test(i.name)).length}));
    if(mapId==='sn09') {
      // Ordinary inputs from the original spawn: move onto the central stone
      // before the outer floors fall, then hold guard while ColdYan acts.
      const goal=host.points.get(4).navigationPosition;
      for(let i=0;i<900&&game.running;i++) {
        const delta=goal.clone().sub(game.hero.root.position);
        if(Math.hypot(delta.x,delta.z)<.7&&game.hero.root.position.y>4)break;
        game.cameraAngle=Math.atan2(-delta.x,-delta.z);game.action('forward');
        if(!game.hero.scriptInputBlocked&&game.hero.grounded&&Math.hypot(delta.x,delta.z)<11)game.action('jump');
        tick(game,1/30);
      }
      game.action('forward',false);game.action('guard');
    }
    for(let i=0;i<(mapId==='sn09'?6300:60) && game.running;i++) {
      if(mapId==='sn09') {
        const goal=host.points.get(4).navigationPosition,delta=goal.clone().sub(game.hero.root.position);
        const move=Math.hypot(delta.x,delta.z)>.6;
        if(move)game.cameraAngle=Math.atan2(-delta.x,-delta.z);
        game.action('forward',move);game.action('guard');
        if(game.hero.grounded&&game.hero.root.position.y<4&&move)game.action('jump');
      }
      tick(game,1/30);
    }
    console.log(mapId, JSON.stringify({time:host.clock,result:host.completed,hero:game.hero.hp,position:game.hero.root.position.toArray(),diagnostics:host.diagnostics,
      source:host.levelVm.snapshot(),collapsed:[...game.currentMap.props.instances.values()].filter(i=>/D_sn09f/.test(i.name)&&i.pose===1).length}));
    f.dispose();
  }
}finally{restore();}
