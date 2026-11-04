// SPDX-License-Identifier: MIT
#pragma once
#include <stdint.h>
namespace nfs_arrival {
struct State {
 uint32_t thresholdQ16=32768,seed=0;bool opened=false;
 struct Human{uintptr_t car=0;int64_t baseline=0;int sections=0;bool reverse=false;};
 Human humans[2];
 void reset(uint32_t value){seed=value*1664525u+1013904223u;thresholdQ16=32768u+seed%98305u;opened=false;for(auto &h:humans)h=Human();}
 bool update(int player,uintptr_t car,int lap,int debt,int section,int sections,bool reverse){
  if(player<0||player>1||!car||sections<100||sections>32767||section<0||section>=sections||lap<0||lap>1000000||debt<0||debt>1000000)return opened;
  const int64_t progress=((int64_t)lap-debt)*sections+(reverse?sections-section:section);
  Human &h=humans[player];
  if(h.car!=car||h.sections!=sections||h.reverse!=reverse){h.car=car;h.baseline=progress;h.sections=sections;h.reverse=reverse;return opened;}
  const int64_t advance=progress>h.baseline?progress-h.baseline:0;
  if(advance*65536>=(int64_t)thresholdQ16*sections)opened=true;
  return opened;
 }
};
}
