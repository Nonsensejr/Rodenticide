#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "xdotool/xdo.h"
#include "rdtc.h"

Display *dis;
xdo_t *xdo;

int startCapture(){
    Window *curWindow;
    xdo_get_window_at_mouse(xdo, curWindow);
    XGrabKeyboard(
            dis, 
            *curWindow, 
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
    dis = XOpenDisplay((char *)0);
    xdo = xdo_new_with_opened_display(dis, "rdtc", True);
    startCapture();
    controlling();
    endCapture();
    return 0;
};


