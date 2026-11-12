import test from 'node:test';import assert from 'node:assert/strict';import * as T from '../dist/vendor/three.module.js';import {MeteorGame} from '../dist/engine.js';import {createPlayerControl} from '../dist/player-control.js';import {acquireCombatTarget} from '../dist/combat-targeting.js';
const actor=(x,z,team=2)=>({root:{position:new T.Vector3(x,0,z),rotation:{y:0}},team,weapon:'sword',grounded:true,rage:100,combat:{busy:false,timeline:{pose:{id:0}},attack(){return true;}}});
function fixture(){const g=Object.create(MeteorGame.prototype),hero=actor(0,0,1),front=actor(1,4),back=actor(0,-2),control=createPlayerControl({cameraAngle:Math.PI});hero.playerControl=control;Object.assign(g,{hero,enemies:[front,back],elapsed:0,hasScriptLineOfSight:()=>true,_emit(){}});return {g,hero,front,back,control};}
test('攻击只自动选择前方可见敌人，忽略队友、身后、隔墙与高差目标',()=>{const {hero,front,back}=fixture(),ally=actor(0,1,1),high=actor(0,3);high.root.position.y=10;assert.equal(acquireCombatTarget(hero,[back,ally,high,front]),front);assert.equal(acquireCombatTarget(hero,[front],{lineOfSight:()=>false}),null);});

test('原阵营位掩码重叠即为同伴，显式掩码优先，零掩码不把所有无阵营角色当同伴',()=>{
 const hero=actor(0,0,1),compound=actor(0,1,3),enemy=actor(0,4,2);
 assert.equal(acquireCombatTarget(hero,[compound,enemy]),enemy);
 compound.teamMask=4;assert.equal(acquireCombatTarget(hero,[compound,enemy]),compound);
 compound.teamMask=1;compound.team=2;assert.equal(acquireCombatTarget(hero,[compound,enemy]),enemy);
 hero.team=0;compound.team=0;compound.teamMask=0;assert.equal(acquireCombatTarget(hero,[compound]),compound);
});
test('锁定保持同一目标，Q解除后连续攻击保持自由朝向，再按恢复锁定',()=>{const {g,hero,front,control}=fixture();assert.equal(g._attackTarget(hero,control),front);g.enemies.push(actor(0,2));assert.equal(g._attackTarget(hero,control),front);g._toggleCombatLock(hero,control);assert.equal(g._attackTarget(hero,control),null);assert.equal(control.autoLockEnabled,false);g._toggleCombatLock(hero,control);assert.ok(control.locked);});

test('未锁鼠且没有新视角输入时自由攻击保留自身朝向，新视角在攻击入口消费',()=>{
 const {g,hero,control}=fixture();g.enemies=[];hero.root.rotation.y=.7;
 assert.equal(g._beginAttack(hero),true);assert.equal(hero.root.rotation.y,.7);
 control.cameraAngle=.2;control.lookPending=true;assert.equal(g._beginAttack(hero),true);
 assert.ok(Math.abs(hero.root.rotation.y-(Math.PI+.2))<1e-9);assert.equal(control.lookPending,false);
});
test('排队连招在实际起手时重新对准移动后的锁定目标，远程瞄准不强制锁人',()=>{const {g,hero,front,control}=fixture();let start;hero.combat.attack=options=>(start=options.onStart,true);assert.equal(g._beginAttack(hero),true);front.root.position.set(4,0,1);start(null);assert.ok(Math.abs(Math.atan2(Math.sin(hero.root.rotation.y-Math.atan2(4,1)),Math.cos(hero.root.rotation.y-Math.atan2(4,1))))<1e-9);control.locked=null;hero.weapon='musket';assert.equal(g._attackTarget(hero,control),null);});
