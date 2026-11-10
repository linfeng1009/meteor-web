import test from 'node:test';
import assert from 'node:assert/strict';
import {bindLocalPlayerControl,createPlayerControl,clearPlayerCommands} from '../dist/player-control.js';

test('local keyboard/camera aliases keep using explicit state after buffers and held keys are replaced',()=>{
  const game={keys:new Set(['left']),directionBuffer:[],cameraAngle:.4,mouseLook:{locked:true}};
  const control=bindLocalPlayerControl(game),remote=createPlayerControl();
  game.keys=new Set(['guard']);game.directionBuffer=[{direction:'up'}];game.cameraAngle=1.2;
  assert.deepEqual([...control.keys],['guard']);assert.equal(control.directionBuffer,game.directionBuffer);assert.equal(control.cameraAngle,1.2);
  control.locked={id:2};assert.equal(game.locked,control.locked);clearPlayerCommands(control);assert.deepEqual(game.directionBuffer,[]);
  game.mouseLook={locked:false};assert.equal(control.mouseLook.locked,false);
  assert.equal(remote.keys.size,0);assert.equal(remote.locked,null);assert.equal(remote.cameraAngle,0);
});
