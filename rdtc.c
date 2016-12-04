#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "xdotool/xdo.h"
#include "rdtc.h"

Display *dis;

int startCapture(){
    XGrabKeyboard(
            dis, 
            DefaultRootWindow( dis ), 
            True, 
            GrabModeAsync, 
            GrabModeSync, 
            CurrentTime );
    return 0;
}

int controlling(){
	XEvent event;
    XKeyEvent kevent;
	while (True){
        XNextEvent(dis, &event);
	    switch (event.type){
            case KeyPress:
                kevent = *(XKeyEvent*)&event;
                printf("%d\n", kevent.keycode);
                break;
        }
        break;
	}
    return 0;
}

int endCapture(){
    XAllowEvents(
            dis,
            SyncKeyboard,
            CurrentTime
            );
    return 0;
}

int main(int argc, char *argv[]){
    dis=XOpenDisplay((char *)0);
    startCapture();
    controlling();
    endCapture();
    return 0;
};


