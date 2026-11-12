import test from 'node:test';
import assert from 'node:assert/strict';
import {SceneryCarousel,sceneryImage} from '../dist/menu-scenery.js';
function setup(){let job=null,active=true,shown=[];const carousel=new SceneryCarousel({show:id=>shown.push(id),active:()=>active,schedule:fn=>(job=fn,1),cancel:()=>job=null});return {carousel,shown,tick(){const current=job;job=null;current?.();},setActive(value){active=value;},pending:()=>!!job};}
test('首页从所选战场开始轮换，轮换不修改外部战场选择',()=>{const s=setup();s.carousel.start('forge');assert.deepEqual(s.shown,['sn10']);s.tick();assert.equal(s.shown.at(-1),'sn14');assert.ok(s.pending());assert.ok(sceneryImage('sifang').endsWith('sn06.webp'));});
test('离开首页、进入战斗或标签页隐藏后不轮换且不继续计时',()=>{const s=setup();s.carousel.start('sn06');s.setActive(false);s.tick();assert.deepEqual(s.shown,['sn06']);assert.equal(s.pending(),false);s.carousel.stop();assert.equal(s.carousel.enabled,false);});
test('暂停保留手动切换能力，恢复时只安排一个任务',()=>{const s=setup();s.carousel.start('qiyun');s.carousel.setPaused(true);assert.equal(s.pending(),false);s.carousel.step(1);assert.equal(s.shown.at(-1),'sn06');assert.equal(s.pending(),false);s.carousel.setPaused(false);assert.equal(s.pending(),true);s.carousel.choose('cave');assert.equal(s.shown.at(-1),'sn01');s.carousel.stop();assert.equal(s.pending(),false);});
