export const NETWORK_PROTOCOL=5;
export const MAX_NETWORK_PLAYERS=16;
export const NETWORK_MODES=Object.freeze({leader:'盟主',deathmatch:'死斗'});
export function roomRules(input={}){
 const rules={mode:input.mode??'leader',maxPlayers:input.maxPlayers??MAX_NETWORK_PLAYERS,scoreLimit:input.scoreLimit??10,timeLimit:input.timeLimit??600};
 if(!Object.hasOwn(NETWORK_MODES,rules.mode)||(!Number.isInteger(rules.maxPlayers)||rules.maxPlayers<2||rules.maxPlayers>MAX_NETWORK_PLAYERS)||![5,10,20].includes(rules.scoreLimit)||![300,600,900].includes(rules.timeLimit))throw Error('房间规则无效');
 return rules;
}
export function matchResult(rules,players,time){
 const present=players.filter(p=>!p.departed);
 if(rules.mode==='deathmatch'){
  const teams=[...new Set(present.filter(p=>!p.dead).map(p=>p.team))];
  if(teams.length<=1)return {reason:'elimination',winnerIds:teams.length?present.filter(p=>p.team===teams[0]).map(p=>p.id):[],winnerTeam:teams[0]??null};
  if(time>=rules.timeLimit)return {reason:'time',winnerIds:[],winnerTeam:null};
 }else if(present.length<2||time>=rules.timeLimit||present.some(p=>p.kills>=rules.scoreLimit)){
  const best=Math.max(0,...present.map(p=>p.kills));return {reason:present.length<2?'departure':time>=rules.timeLimit?'time':'score',winnerIds:present.filter(p=>p.kills===best).map(p=>p.id),winnerTeam:null};
 }
 return null;
}
