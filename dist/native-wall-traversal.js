import {NATIVE_AIR_PHYSICS} from './native-traversal.js';
// Native 004ccc70: wall poses 161/162/163 leave via 157/159/160.
// Actual POS links supply their corresponding air recovery poses.
export const NATIVE_WALL_POSES=Object.freeze({
  front:Object.freeze({pose:161,exit:157}),
  right:Object.freeze({pose:162,exit:159}),
  left:Object.freeze({pose:163,exit:160})
});
// 004cd1f0: wall-state clock+138 < float64(1.8), held forward=1;
// velocity += dt*(float32(-1.2)*velocity + gravity*float32(.1)).
export const NATIVE_WALL_PHYSICS=Object.freeze({duration:1.8,damping:Math.fround(1.2),gravityScale:Math.fround(.1)});
export function nativeWallVerticalVelocity(velocity,dt,gravity){
  const native=velocity/.08;
  return Math.fround(native+(-NATIVE_WALL_PHYSICS.damping*native-gravity/.08*NATIVE_WALL_PHYSICS.gravityScale)*dt)*.08;
}
// 004cf670..004cf70b: copy saved collision normal, add1 to native Z,
// normalize, then multiply by282/375. Web uses Y as its up axis.
export function nativeWallJumpVelocity(normal,{large=false}={}){
  const x=normal.x,y=Math.fround(normal.y+1),z=normal.z,length=Math.hypot(x,y,z);
  if(!(length>0))return null;
  const speed=(large?NATIVE_AIR_PHYSICS.largeJumpVelocity:NATIVE_AIR_PHYSICS.jumpVelocity)/.08;
  return {x:Math.fround(Math.fround(x/length)*speed)*.08,
    y:Math.fround(Math.fround(y/length)*speed)*.08,z:Math.fround(Math.fround(z/length)*speed)*.08};
}
// Explicit browser contact/physics adapter, NOT recovered EXE constants.
// One bounded wall contact per airborne period prevents unlimited wall climbing.
export const WALL_TRAVERSAL_ADAPTER=Object.freeze({reach:.2,heights:Object.freeze([.85,1.6]),maxNormalY:.25,
  sideSpeed:6,kickDuration:.25,maxEntries:1,bodyHeight:2.2});
