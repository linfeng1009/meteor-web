// Prefer native spawn/waypoint positions. Extra slots must have a nearby floor,
// clear path from their anchor, and room for a separate fighter capsule.
export function networkSpawns(game,count){
  const map=game.currentMap,chosen=[];
  const add=(spawn,anchor)=>{if(!spawn?.position)return;const p=spawn.position.clone();if(anchor&&game._horizontalBlocked?.(anchor.position,p.x-anchor.position.x,p.z-anchor.position.z))return;const hit=game._ground?.(p.x,p.z,p.y+3);if(!hit||Math.abs(hit.point.y-p.y)>3)return;p.y=hit.point.y;if(chosen.some(s=>Math.hypot(s.position.x-p.x,s.position.z-p.z)<1.5))return;chosen.push({...spawn,position:p});};
  for(const spawn of map.spawns){add(spawn);if(chosen.length>=count)return chosen;}
  for(const point of map.points||[]){add({name:`network-wp-${point.id}`,position:point.position});if(chosen.length>=count)return chosen;}
  const anchors=[...chosen];
  for(const radius of [2,3.5,5,7])for(const anchor of anchors)for(let i=0;i<12;i++){const position=anchor.position.clone();position.x+=Math.cos(i*Math.PI/6)*radius;position.z+=Math.sin(i*Math.PI/6)*radius;add({name:`network-extra-${chosen.length}`,position},anchor);if(chosen.length>=count)return chosen;}
  throw Error(`当前战场只有 ${chosen.length} 个安全出生点，无法容纳 ${count} 人`);
}
