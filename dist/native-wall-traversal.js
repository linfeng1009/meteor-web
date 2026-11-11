// Native 004ccc70: wall poses 161/162/163 leave via 157/159/160.
// Actual POS links supply their corresponding air recovery poses.
export const NATIVE_WALL_POSES=Object.freeze({
  front:Object.freeze({pose:161,exit:157}),
  right:Object.freeze({pose:162,exit:159}),
  left:Object.freeze({pose:163,exit:160})
});
// Explicit browser contact/physics adapter, NOT recovered EXE constants.
// One bounded wall contact per airborne period prevents unlimited wall climbing.
export const WALL_TRAVERSAL_ADAPTER=Object.freeze({reach:.2,heights:Object.freeze([.85,1.6]),maxNormalY:.25,
  duration:.65,frontRise:4,sideRise:0,sideSpeed:6,kickSpeed:8,kickDuration:.25,maxEntries:1,bodyHeight:2.2});
