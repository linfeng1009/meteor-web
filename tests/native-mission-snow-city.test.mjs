import test, { after } from 'node:test';
import assert from 'node:assert/strict';
import { nativeFiles, nativeMission, tick, attackWhenReady, v } from './helpers/native-mission-fixture.mjs';
import { NativeWeather } from '../dist/native-weather.js';
import * as THREE from '../dist/vendor/three.module.js';

const restore = nativeFiles(), fixtures=[];
async function mission() { const fixture=await nativeMission('sn04');fixtures.push(fixture);return fixture; }
after(()=>{for(const fixture of fixtures)fixture.dispose();restore();});

test('snow city starts with source seven guards, both original weapons, five weather settings and10000HP gates', async()=>{
  const {game,host}=await mission();
  assert.equal(game.hero.hp,2000);assert.equal(game.hero.weaponId,16);assert.equal(game.hero.weapon2Id,13);
  assert.equal(game.hero.team,1);assert.equal(game.enemies.length,7);
  assert.deepEqual(game.enemies.map(actor=>[actor.scriptId,actor.modelId,actor.weaponId,actor.hp,actor.team]).sort((a,b)=>a[0]-b[0]),[
    [1,6,17,5000,2],[2,8,25,2500,2],[3,8,25,2500,2],[4,5,12,1500,2],[5,5,12,1500,2],[6,9,17,2500,2],[7,9,18,2500,2]
  ]);
  assert.equal(host.sceneVm.getGlobal('g_iPdoorMaxHP'),10000);
  assert.equal(host.sceneVm.getGlobal('g_iBPdoorHP'),10000);assert.equal(host.sceneVm.getGlobal('g_iAPdoorHP'),10000);
  assert.deepEqual(host.sceneSettings,{snow:[1],snowdensity:[200],winddir:[50,0,0],snowspeed:[20,100],snowsize:[5,5]});
  assert.equal(game.weather.points.geometry.attributes.position.count,200);
  assert.equal(game.missionState.objective.targetHp,10000);assert.equal(game.missionState.objective.position.x,game.getSceneObject('D_BPdoor').root.position.x);
  assert.equal(host.diagnostics.length,0);assert.equal(game.currentMap.props.warnings.length,0);
});

test('source spear contacts break the enemy gate through all source stages and wait for its final FMC frame before victory', async t=>{
  const {game,host,endings}=await mission();
  for(let frame=0;frame<750;frame++)tick(game,1/30,{enemies:false});
  const originalHP=game.enemies.map(actor=>actor.hp),gate=game.getSceneObject('D_BPdoor');
  // Controlled contact acceptance: put the player beside the source gate once,
  // freeze NPC combat/navigation, then use only ordinary movement/A inputs.
  // Gate HP, source globals, actor HP and the result are never assigned.
  game._placeFighter(game.hero,{position:gate.root.position.clone().add(v(-3,0,0))});
  game.hero.root.rotation.y=Math.PI/2;game.cameraAngle=-Math.PI/2;game.locked=null;
  const damage=game.sceneDamageResolver({attacker:game.hero,state:{poseId:279}});
  host.sceneItemAttack('D_APdoor',0,damage);assert.equal(host.sceneVm.getGlobal('g_iAPdoorHP'),10000,'source friendly gate is immune to Team1');
  const stages=new Set();let lastApproach=-Infinity,sawDestruction=false;
  for(let frame=0;frame<9000&&game.running;frame++) {
    const approach=game.hero.root.position.x<gate.root.position.x-3.2;
    game.action('forward',approach);if(approach)lastApproach=game.elapsed;
    if(!approach&&game.elapsed-lastApproach>.5)attackWhenReady(game);
    tick(game,1/30,{enemies:false});stages.add(host.sceneVm.getGlobal('g_iBPdoorState'));
    if(gate.pose===8&&gate.state!==3){sawDestruction=true;assert.equal(host.completed,undefined,'must wait for the original collapse animation');}
  }
  assert.deepEqual([...stages].sort(),[1,2,3,4,5]);assert.ok(host.sceneVm.getGlobal('g_iBPdoorHP')<0);assert.ok(sawDestruction);
  assert.equal(gate.pose,8);assert.equal(gate.state,3);assert.equal(gate.attributes.interactive,0);
  assert.equal(host.completed.win,true);assert.equal(host.completed.reason,'script-gate-destroyed');assert.equal(endings.length,1);
  assert.equal(game.kills,0);assert.equal(game.hero.hp,2000);assert.deepEqual(game.enemies.map(actor=>actor.hp),originalHP);
  assert.equal(host.diagnostics.length,0);t.diagnostic(`Source gate victory at${host.clock.toFixed(2)}s; isolated contact fixture, not live-AI completion.`);
  await game.start({map:'sn04',mode:'story'});
  assert.equal(game.missionHost.sceneVm.getGlobal('g_iBPdoorHP'),10000);assert.equal(game.getSceneObject('D_BPdoor').pose,0);
  assert.equal(game.weather.clock,0);assert.equal(game.hero.hp,2000);assert.equal(game.enemies.length,7);
});

test('weather updates do not draw combat randomness and leaving disposes its scene objects', async()=>{
  const scene=new THREE.Scene(),weather=new NativeWeather(scene);let draws=0;const random=Math.random;
  Math.random=()=>{draws++;return .5;};
  try {
    for(const [name,args]of Object.entries({snow:[1],snowdensity:[200],winddir:[50,0,0],snowspeed:[20,100],snowsize:[5,5]}))assert.equal(weather.set(name,...args),true);
    const constructionDraws=draws;weather.update(.5,v(10,2,5));assert.equal(draws,constructionDraws,'Three.js constructors may generate UUIDs, but weather updates must not change combat RNG per frame');assert.equal(weather.clock,.5);
    assert.ok([...weather.points.geometry.attributes.position.array].every(Number.isFinite));
    assert.equal(weather.set('unknown',1),false);assert.equal(weather.set('winddir',1),false);
    weather.dispose();assert.equal(scene.children.length,0);assert.deepEqual(weather.settings,{});
  } finally { Math.random=random; }
  const {game,host}=await mission();const old=game.weather.points;host.dispose();assert.equal(game.weather.points,null);assert.equal(old.parent,null);
});
