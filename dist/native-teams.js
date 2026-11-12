// Reference004f2af0 compares the local team mask with the target mask;
// a shared bit means friendly.004f2ab0 optionally bypasses this relation
// through world+2278. That full native mode switch remains unported.
export function nativeTeamMask(actor,fallback=0){return Number(actor?.teamMask??actor?.team??fallback)|0;}
export function nativeSameTeam(actor,target){return (nativeTeamMask(actor)&nativeTeamMask(target))!==0;}
