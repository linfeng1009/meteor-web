// 004cbf10 maps f/r/l/b to176/177/178/179 when crouched (vtable+110).
// The .3s double-tap interval is a Web recognizer adapter based on the native
// command-token lifetime; exact original double-tap sampling remains unverified.
export const NATIVE_TRAVERSAL_WINDOW=.3;
// Reference EXE 004cb083 initializes actor+0xd8 to float32(-882);
// 004cf5a0 assigns float32(282) to actor+0x398 for jump argument0.
// 004ce840 consumes the gravity vector during attack/free-flight motion.
// 004cf4b0 starts the button timer;004cf530 selects the jump on release,
// comparing against float64(.11) at005aa8e8.004cd3a0 auto-releases after it.
// Collision shape, horizontal steering and wall traversal remain Web adapters.
export const NATIVE_JUMP_HOLD_SECONDS=.11;
// 004cb5e0 passes mouseX*(world.mouseSpeed+1)*float32(1/140) to
// 004cc640; native default speed50 is initialized at00486a28. That handler
// selects right141/left142 only beyond±1 and restarts actor+1c8.004cd3a0
// returns to stance after its clock exceeds float64(.2) at005a8f90.
export const NATIVE_STANDING_TURN=Object.freeze({hold:.2,mouseSpeed:50,inputScale:Math.fround(1/140)});
export function nativeStandingTurnDirection(mouseX){
  const value=Math.fround(mouseX*(NATIVE_STANDING_TURN.mouseSpeed+1)*NATIVE_STANDING_TURN.inputScale);
  return value>1?'right':value< -1?'left':null;
}
// 004ce840 damps actor+3b8/+3bc by1-(grounded?9:.2)*dt.
// Ninja004e34e0 scales those fields byfloat32(.67) on an accepted attack.
export const NATIVE_ACTION_MOTION=Object.freeze({groundDamping:9,airDamping:Math.fround(.2),ninjaScale:Math.fround(.67)});
export function nativeActionMomentum(velocity,dt,grounded){
  const factor=1-(grounded?NATIVE_ACTION_MOTION.groundDamping:NATIVE_ACTION_MOTION.airDamping)*dt;
  return Math.fround(velocity/.08*factor)*.08;
}
// 004cd3a0 calls004cf7c0 only below float32(-40) native vertical
// speed. The initializer preserves existing air/fall clips, otherwise maps
// directional takeoff153/155/157 to154/156/158, default152.
export function nativeAirPose(current,vertical){
  if(!(Math.fround(vertical/.08)<-40))return current;
  switch(current){
    case 152:case 154:case 156:case 158:case 180:return current;
    case 153:return 154;
    case 155:return 156;
    case 157:return 158;
    default:return 152;
  }
}
export const NATIVE_AIR_PHYSICS=Object.freeze({gravity:882*.08,jumpVelocity:282*.08,largeJumpVelocity:375*.08,
  provenance:'Reference Meteor.exe constructor004cb083 immc45c8000;004cf5a0 uses005aa93c float282 or005aa940 float375.004cf530 hold threshold float64(.11) at005aa8e8. Native units×.08.'});
// 004cd3a0 state0 applies linear drag(.1*200) before gravity, then
// quadratic drag(.1/600). Horizontal steering remains the Web host adapter.
export function nativeAirVerticalVelocity(vertical,horizontal,dt,gravity=NATIVE_AIR_PHYSICS.gravity){
  let velocity=vertical/.08,speed=Math.hypot(velocity,horizontal/.08);
  if(speed>0)velocity=Math.fround(velocity*Math.max(0,1-20*dt/speed));
  velocity=Math.fround(velocity-gravity/.08*dt);speed=Math.hypot(velocity,horizontal/.08);
  return Math.fround(velocity*Math.max(0,1-speed*dt/6000))*.08;
}
export const NATIVE_ROLL_POSES=Object.freeze({forward:176,right:177,left:178,back:179});
// 004cc730 maps crouched idle -> 10 and walk/run 140/144,141,142,143
// to 145,146,147,148. 004cf770 selects directional takeoff; 004cf7d0
// keeps the corresponding air pose (151/152,153/154,155/156,157/158).
export const NATIVE_CROUCH_POSES=Object.freeze({idle:10,forward:145,right:146,left:147,back:148});
// Directional ground clips consumed by the same 004cc730 remapping path.
// Forward retains the existing run adapter; 140 is a separate slow walk.
export const NATIVE_GROUND_MOVE_POSES=Object.freeze({forward:144,right:141,left:142,back:143});
export const NATIVE_JUMP_POSES=Object.freeze({forward:Object.freeze({start:151,air:152}),right:Object.freeze({start:153,air:154}),left:Object.freeze({start:155,air:156}),back:Object.freeze({start:157,air:158})});
export function nativeTraversalDirection(keys){
  const forward=Number(!!keys?.has('forward'))-Number(!!keys?.has('back'));
  const right=Number(!!keys?.has('right'))-Number(!!keys?.has('left'));
  return forward>0?'forward':forward<0?'back':right>0?'right':right<0?'left':null;
}
const poses=(forward,right,left,back)=>Object.freeze({forward,right,left,back});
// 004cbf10 dispatches standing f/r/l/b as164/167/170/173 through weapon+28.
// Verified remappers: dd790 sword, ddef0 spear, de640 blade, df600 dart,
// dee40 musket, dfd50 wheel, e2860 qiankun, e3c00 knuckle.
export const NATIVE_DASH_POSES=Object.freeze({sword:poses(165,168,171,174),spear:poses(166,169,172,175),blade:poses(165,168,171,174),
  dart:poses(164,167,170,173),musket:poses(164,167,170,173),wheel:poses(166,169,172,175),qiankun:poses(505,506,507,508),knuckle:poses(509,510,511,512)});
export const nativeDashPose=(weapon,direction)=>NATIVE_DASH_POSES[weapon]?.[direction]??null;
export function traversalTap(previous,{direction,time,crouched,allowed,weapon}){
  if(!allowed||!Object.hasOwn(NATIVE_ROLL_POSES,direction)||!Number.isFinite(time))return {tap:null,poseId:null};
  const tap={direction,time,crouched:!!crouched,weapon};
  const matched=previous&&!!previous.crouched===!!crouched&&previous.direction===direction&&(crouched||previous.weapon===weapon)&&time>previous.time&&time-previous.time<=NATIVE_TRAVERSAL_WINDOW;
  const poseId=matched?(crouched?NATIVE_ROLL_POSES[direction]:nativeDashPose(weapon,direction)):null;
  return {tap:poseId?null:tap,poseId};
}
