// 004cbf10 maps f/r/l/b to176/177/178/179 when crouched (vtable+110).
// The .3s double-tap interval is a Web recognizer adapter based on the native
// command-token lifetime; exact original double-tap sampling remains unverified.
export const NATIVE_TRAVERSAL_WINDOW=.3;
export const NATIVE_ROLL_POSES=Object.freeze({forward:176,right:177,left:178,back:179});
export function traversalTap(previous,{direction,time,crouched,allowed}){
  if(!allowed||!Object.hasOwn(NATIVE_ROLL_POSES,direction)||!Number.isFinite(time))return {tap:null,poseId:null};
  const tap={direction,time,crouched:!!crouched};
  const matched=crouched&&previous?.crouched&&previous.direction===direction&&time>previous.time&&time-previous.time<=NATIVE_TRAVERSAL_WINDOW;
  return {tap:matched?null:tap,poseId:matched?NATIVE_ROLL_POSES[direction]:null};
}
