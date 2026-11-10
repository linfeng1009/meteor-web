import * as THREE from '../dist/vendor/three.module.js';
import { nativeFiles, nativeMission, tick, attackWhenReady, v } from '../tests/helpers/native-mission-fixture.mjs';
const restore = nativeFiles();
let fixture;
try {
  fixture = await nativeMission(process.argv[2] || 'sn04');
  const { game, host } = fixture;
  console.log('source', JSON.stringify({hp:game.hero.hp, weapon:game.hero.weaponId, actors:[...host.actors.values()].map(a=>[a.name,a.hp,a.weaponId,a.team]), diagnostics:host.diagnostics}));
  for (const name of ['D_APdoor', 'D_BPdoor', 'D_BPd02Box']) {
    const obj = game.getSceneObject(name); if (!obj) continue;
    const box = new THREE.Box3().setFromObject(obj.root);
    console.log(name, JSON.stringify({position:obj.root.position.toArray(), min:box.min.toArray(),max:box.max.toArray(),colliders:obj.colliders.length,attr:obj.attributes,poses:obj.asset.poses}));
  }
  for (let i=0; i<750; i++) tick(game,1/30,{player:false,enemies:false});
  console.log('intro', host.clock, game.hero.scriptInputBlocked, host.diagnostics, host.sceneSettings);
  if (process.argv.includes('--gate')) {
    const gate = game.getSceneObject('D_BPdoor');
    game._placeFighter(game.hero,{position:gate.root.position.clone().add(v(-3,0,0))});
    game.hero.root.rotation.y=Math.PI/2; game.locked=null;
    game.cameraAngle=-Math.PI/2;
    let before=10000, lastApproach=-Infinity;
    for(let frame=0;frame<45000 && game.running;frame++) {
      const approach=game.hero.root.position.x<gate.root.position.x-3.2;
      game.action('forward',approach);
      if(approach)lastApproach=game.elapsed;
      if(!approach && game.elapsed-lastApproach>.5)attackWhenReady(game);
      tick(game,1/30,{enemies:false});
      const hp=host.sceneVm.getGlobal('g_iBPdoorHP');
      if(hp!==before && (before===10000||Math.floor(hp/1000)!==Math.floor(before/1000)))console.log('gate-hit',frame,hp,game.hero.root.position.toArray(),gate.pose,gate.state);
      before=hp;
    }
    console.log('gate-end',host.clock,host.sceneVm.getGlobal('g_iBPdoorHP'),host.completed,game.hero.hp,host.diagnostics);
  }
} finally { fixture?.dispose(); restore(); }
