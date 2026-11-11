// 004cbf10 maps f/r/l/b to176/177/178/179 when crouched (vtable+110).
// The .3s double-tap interval is a Web recognizer adapter based on the native
// command-token lifetime; exact original double-tap sampling remains unverified.
export const NATIVE_TRAVERSAL_WINDOW=.3;
export const NATIVE_ROLL_POSES=Object.freeze({forward:176,right:177,left:178,back:179});
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
