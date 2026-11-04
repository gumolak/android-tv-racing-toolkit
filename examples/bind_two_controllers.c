/* SPDX-License-Identifier: MIT
 * Raw SDL2 event demo; no Android activity, persistent identity, or game code. */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include "racing_toolkit/ControllerIdentity.h"
int main(void){
 SDL_SetMainReady();
 if(SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_EVENTS)!=0){fprintf(stderr,"%s\n",SDL_GetError());return 1;}
 SDL_Joystick *pads[2]={NULL,NULL};SDL_JoystickID ids[2]={-1,-1};
 for(int i=0,p=0;i<SDL_NumJoysticks()&&p<2;++i){
  SDL_Joystick *pad=SDL_JoystickOpen(i);if(!pad)continue;
  SDL_JoystickID id=SDL_JoystickInstanceID(pad);
  if(id<0||id==ids[0]){SDL_JoystickClose(pad);continue;}
  pads[p]=pad;ids[p]=id;++p;
 }
 if(ids[0]<0||ids[1]<0){fprintf(stderr,"Connect two distinct joysticks before running.\n");goto finish;}
 nfs_order_configure(1,3,ids[0],ids[1]);nfs_order_publish(0,ids[0]);nfs_order_publish(1,ids[1]);
 puts("Listening to raw buttons. Disconnect a controller to exit; restart after reconnecting.");
 for(;;){SDL_Event e;if(!SDL_WaitEvent(&e))break;
  if(e.type==SDL_JOYDEVICEREMOVED||e.type==SDL_QUIT)break;
  if(e.type==SDL_JOYBUTTONDOWN){int p=nfs_order_find_bound(e.jbutton.which);
   if(p>=0&&nfs_order_filter(p,e.jbutton.which))printf("P%d button %u\n",p+1,(unsigned)e.jbutton.button);
  }
 }
finish:
 for(int p=0;p<2;++p)if(pads[p])SDL_JoystickClose(pads[p]);
 SDL_Quit();return ids[0]<0||ids[1]<0?1:0;
}
