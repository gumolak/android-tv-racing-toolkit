// SPDX-License-Identifier: MIT
#include "racing_toolkit/ControllerIdentity.h"
static SDL_SpinLock orderLock=0;
static int orderEnabled=0,orderMask=0;
static SDL_JoystickID desired[2]={-1,-1};
static SDL_atomic_t bound[2]={{-1},{-1}};
void nfs_order_configure(int enabled,int mask,SDL_JoystickID first,SDL_JoystickID second){
 SDL_AtomicLock(&orderLock);orderEnabled=enabled;orderMask=mask;desired[0]=first;desired[1]=second;SDL_AtomicUnlock(&orderLock);
}
int nfs_order_mode(void){int n;SDL_AtomicLock(&orderLock);n=orderEnabled;SDL_AtomicUnlock(&orderLock);return n;}
int nfs_order_filter(int slot,SDL_JoystickID instance){
 if(slot<0||slot>1||instance<0)return 0;
 int enabled,mask;SDL_JoystickID own,other;
 SDL_AtomicLock(&orderLock);enabled=orderEnabled;mask=orderMask;own=desired[slot];other=desired[1-slot];SDL_AtomicUnlock(&orderLock);
 if(!enabled)return 1;
 if(mask&(1<<slot))return own>=0&&instance==own;
 return instance!=other; // Unassigned newcomer may join, but cannot take the known partner's device.
}
void nfs_order_publish(int slot,SDL_JoystickID instance){if(slot>=0&&slot<2){SDL_AtomicLock(&orderLock);SDL_AtomicSet(&bound[slot],instance);SDL_AtomicUnlock(&orderLock);}}
int nfs_order_find_bound(SDL_JoystickID instance){
 if(instance<0)return -1;int a,b;SDL_AtomicLock(&orderLock);a=SDL_AtomicGet(&bound[0])==instance;b=SDL_AtomicGet(&bound[1])==instance;SDL_AtomicUnlock(&orderLock);
 return a==b?-1:a?0:1; // Never return a player for an ambiguous duplicate instance.
}
