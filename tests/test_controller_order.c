/* SPDX-License-Identifier: MIT */
#include <stdio.h>
#include "racing_toolkit/ControllerIdentity.h"
static int checks;
#define CHECK(x) do { ++checks; if(!(x)){fprintf(stderr,"registry check %d failed at line %d\n",checks,__LINE__);return 1;} }while(0)
void SDL_AtomicLock(SDL_SpinLock *x){(void)x;}
void SDL_AtomicUnlock(SDL_SpinLock *x){(void)x;}
int SDL_AtomicSet(SDL_atomic_t*x,int n){int old=x->value;x->value=n;return old;}
int SDL_AtomicGet(SDL_atomic_t*x){return x->value;}
int main(void){
 nfs_order_configure(1,3,22,11);
 CHECK(nfs_order_mode()==1);
 CHECK(nfs_order_filter(0,22)&&nfs_order_filter(1,11));
 CHECK(!nfs_order_filter(0,11)&&!nfs_order_filter(1,22));
 CHECK(!nfs_order_filter(0,33));
 CHECK(!nfs_order_filter(-1,22)&&!nfs_order_filter(2,22));
 CHECK(!nfs_order_filter(0,-1));
 nfs_order_configure(1,3,-1,11);
 CHECK(!nfs_order_filter(0,11)&&!nfs_order_filter(0,33));
 CHECK(nfs_order_filter(1,11));
 nfs_order_configure(1,1,22,-1);
 CHECK(nfs_order_filter(1,33)&&!nfs_order_filter(1,22));
 nfs_order_publish(0,22);nfs_order_publish(1,33);
 CHECK(nfs_order_find_bound(22)==0&&nfs_order_find_bound(33)==1);
 nfs_order_publish(1,22);CHECK(nfs_order_find_bound(22)==-1);
 nfs_order_publish(1,-1);CHECK(nfs_order_find_bound(22)==0&&nfs_order_find_bound(-1)==-1);
 nfs_order_configure(1,3,44,33);
 CHECK(!nfs_order_filter(0,22)&&nfs_order_filter(0,44));
 nfs_order_publish(0,44);CHECK(nfs_order_find_bound(44)==0);
 nfs_order_configure(0,0,-1,-1);CHECK(nfs_order_filter(0,99)&&nfs_order_filter(1,99));
 printf("Registry policy: %d checks PASS (single-thread SDL stub, no hardware claim)\n",checks);
 return 0;
}
