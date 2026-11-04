// SPDX-License-Identifier: MIT
#pragma once
namespace nfs_stop {
inline bool eligible(int level,int phase,double ahead,double lane,double height,double heading,double human){return level==2&&phase==2&&ahead>=4.&&ahead<=25.&&lane>=-1.2&&lane<=1.2&&height>=-3.&&height<=3.&&heading>=.9&&human>=50./36.;}
struct State{
 int car=0,target=0;unsigned last=0,elapsed=0;bool have=false;double entry=0;
 unsigned clockLast=0;bool clockHave=false;
 void reset(){*this=State();}
 // Call with the canonical accumulated active clock, not a sampled frame dt.
 double goalAtClock(int c,int t,unsigned activeClock,bool valid,double base){
  if(!valid){reset();return base;}
  unsigned delta=clockHave?activeClock-clockLast:0;
  if(!clockHave||car!=c||target!=t||delta>0x7fffffffu){
   reset();car=c;target=t;entry=base<0?0:base;clockHave=true;delta=0;
  }
  clockLast=activeClock;
  if(delta>250)delta=250;
  elapsed+=delta;if(elapsed>3000)elapsed=3000;
  const double ramp=entry*(3000-elapsed)/3000.;return ramp<base?ramp:base;
 }
 double goal(int c,int t,unsigned frame,unsigned dt,bool valid,double base){
  if(!valid){reset();return base;}
  // Initialisation and consumption are separate: dt0 must not claim this frame.
  if(car!=c||target!=t||(have&&(int)(frame-last)<0)){reset();car=c;target=t;entry=base<0?0:base;}
  if((!have||frame!=last)&&dt&&dt<=250){elapsed+=dt;if(elapsed>3000)elapsed=3000;last=frame;have=true;}
  double ramp=entry*(3000-elapsed)/3000.;return ramp<base?ramp:base;
 }
};
}
