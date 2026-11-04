// SPDX-License-Identifier: MIT
#include <cstdio>
#include "racing_toolkit/MenuConfirmMask.h"
#include "racing_toolkit/StopRamp.h"
#include "racing_toolkit/RandomArrival.h"
static int checks;
#define CHECK(x) do{++checks;if(!(x)){std::fprintf(stderr,"policy check %d failed line %d\n",checks,__LINE__);return 1;}}while(0)
int main(){
 using nfs_menu_confirm::filter;
 CHECK(filter(0)==0);CHECK(filter(0x7800)==0);CHECK(filter(0x7801)==1);
 for(unsigned bit=0;bit<32;++bit)CHECK(filter(1u<<bit)==((bit>=11&&bit<=14)?0u:(1u<<bit)));
 nfs_stop::State ramp;
 CHECK(ramp.goalAtClock(1,2,1000,true,30)==30&&ramp.elapsed==0);
 ramp.goalAtClock(1,2,1100,true,30);CHECK(ramp.elapsed==100);
 ramp.goalAtClock(1,2,1100,true,30);CHECK(ramp.elapsed==100);
 ramp.goalAtClock(1,2,9000,true,30);CHECK(ramp.elapsed==350);
 for(unsigned t=9250;t<=12000;t+=250)ramp.goalAtClock(1,2,t,true,30);
 CHECK(ramp.elapsed==3000&&ramp.goalAtClock(1,2,12000,true,30)==0);
 CHECK(ramp.goalAtClock(1,2,12000,false,20)==20&&!ramp.clockHave);
 ramp.goalAtClock(1,2,10,true,20);ramp.goalAtClock(1,3,20,true,25);CHECK(ramp.elapsed==0&&ramp.entry==25);
 ramp.goalAtClock(1,3,5,true,25);CHECK(ramp.elapsed==0);
 ramp.reset();ramp.goalAtClock(1,2,0xfffffff0u,true,30);ramp.goalAtClock(1,2,0x10u,true,30);CHECK(ramp.elapsed==32);
 nfs_arrival::State event;event.reset(7);unsigned chosen=event.thresholdQ16;
 CHECK(chosen>=32768&&chosen<=131072);event.update(0,1,0,0,5,1000,false);CHECK(event.thresholdQ16==chosen&&!event.opened);
 event.thresholdQ16=32768;CHECK(!event.update(0,1,0,0,504,1000,false));CHECK(event.update(0,1,0,0,505,1000,false));CHECK(event.update(0,1,0,0,5,1000,false));
 event.reset(7);CHECK(!event.opened&&event.thresholdQ16==chosen);
 event.thresholdQ16=98304;event.update(0,1,0,0,5,1000,false);CHECK(!event.update(0,1,1,0,504,1000,false));CHECK(event.update(0,1,1,0,505,1000,false));
 event.reset(8);event.thresholdQ16=131072;event.update(0,1,0,0,5,1000,false);CHECK(!event.update(0,1,2,0,4,1000,false));CHECK(event.update(0,1,2,0,5,1000,false));
 event.reset(9);event.thresholdQ16=32768;event.update(0,1,0,0,995,1000,false);CHECK(!event.update(0,1,1,0,494,1000,false));CHECK(event.update(0,1,1,0,495,1000,false));
 event.reset(9);event.thresholdQ16=32768;event.update(0,1,0,0,5,1000,false);CHECK(!event.update(0,1,0,1,995,1000,false));CHECK(!event.update(0,1,0,0,5,1000,false));
 event.reset(9);event.thresholdQ16=32768;event.update(0,1,0,1,5,1000,true);CHECK(!event.update(0,1,0,0,506,1000,true));CHECK(event.update(0,1,0,0,505,1000,true));
 event.reset(9);event.thresholdQ16=32768;event.update(0,1,0,0,5,1000,false);event.update(1,2,0,0,10,1000,false);CHECK(event.update(1,2,0,0,510,1000,false));
 event.reset(9);CHECK(!event.update(2,1,0,0,0,1000,false)&&!event.update(0,0,0,0,0,1000,false));
 for(unsigned seed=0;seed<10000;++seed){event.reset(seed);if(event.thresholdQ16<32768||event.thresholdQ16>131072)return 1;}
 std::printf("Timing and mask policies: %d checks PASS plus10000 seed bounds\n",checks);
 return 0;
}
