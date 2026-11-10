// Read-only reproduction of current production movement at different render rates.
// No renderer, DOM, service or original game process is started.
import {MeteorGame} from '../dist/engine.js';
import * as THREE from '../dist/vendor/three.module.js';
const results=[];
for(const hz of [30,60,144]){
  const game=Object.create(MeteorGame.prototype);
  Object.assign(game,{hostPhysics:{step:.55,gravity:34},currentMap:{bounds:{min:{y:-1000}}},_horizontalBlocked:()=>false,_ground:()=>null});
  const actor={root:new THREE.Group(),velocity:new THREE.Vector3(),grounded:false,vy:0,combat:{busy:false}};
  actor.root.position.y=100;
  for(let i=0;i<hz;i++)game._move(actor,new THREE.Vector3(1,0,0),8,1/hz);
  results.push({hz,seconds:1,x:actor.root.position.x,y:actor.root.position.y});
}
console.log(JSON.stringify({scope:'Production _move, no ground/walls, initial y100, speed8, gravity34. Not an original-game comparison.',results,
  currentFrameClamp:{wallSeconds:1,renderHz:10,simulationSeconds:10*Math.min(.05,.1)}},null,2));
