// A finite measurement keeps long frames, unlike a rolling HUD or load filter.
export function summarizeFrameTrial(frames, phases) {
  if (!frames.length || frames.some(ms => !Number.isFinite(ms) || ms <= 0)) throw new Error('Invalid frame samples');
  const sorted = [...frames].sort((a,b)=>a-b), total = frames.reduce((a,b)=>a+b,0);
  const percentile = p => sorted[Math.ceil(sorted.length*p)-1];
  const average = key => phases.reduce((sum,phase)=>sum+(phase[key]||0),0)/Math.max(1,phases.length);
  return { frames:frames.length, durationMs:total, fps:1000*frames.length/total, p95Ms:percentile(.95), p99Ms:percentile(.99), maxMs:sorted.at(-1),
    over25Ms:frames.filter(ms=>ms>25).length, over50Ms:frames.filter(ms=>ms>50).length,
    cpuMs:average('cpu'), worldMs:average('world'), cameraMs:average('camera'), renderSubmitMs:average('render') };
}

export function assessFrameTrial(report) {
  const reasons=[];
  if(report.hidden)reasons.push('页面曾隐藏');
  if(report.resized)reasons.push('采样期间画面尺寸变化');
  if(report.invalidState||![report.angleChange,report.angleTravel,report.displacement].every(Number.isFinite))reasons.push('视角或角色位移包含无效数值，请刷新后重测');
  // Keep every long frame in the numeric result. A one-second cadence needs
  // review for browser/window throttling rather than silently discarding it.
  if(report.maxMs>=500)reasons.push('存在超过500ms停顿，需排查窗口限速或真实卡顿');
  if(report.mode==='manual'&&(!(report.lockedEvents>0)||!((report.angleTravel??Math.abs(report.angleChange))>1e-6)))reasons.push('未验证锁定鼠标事件驱动了视角');
  return {validForComparison:reasons.length===0,reviewReasons:reasons};
}
