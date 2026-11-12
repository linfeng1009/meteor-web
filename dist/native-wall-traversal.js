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
// Explicit browser contact/physics adapter, NOT recovered EXE constants.
// One bounded wall contact per airborne period prevents unlimited wall climbing.
export const WALL_TRAVERSAL_ADAPTER=Object.freeze({reach:.2,heights:Object.freeze([.85,1.6]),maxNormalY:.25,
  sideSpeed:6,kickSpeed:8,kickDuration:.25,maxEntries:1,bodyHeight:2.2});
