#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "xdotool/xdo.h"
#include "rdtc.h"

int isMovement(int keyCode){
    for(int i = 0; i < sizeof(MOVEMENT_KEYS);i++){
        if(keyCode == MOVEMENT_KEYS[i]) return True;
    }
    return False;
}

int startCapture(xdo_t *xdo, Display *dis){
    XGrabKeyboard(
            dis, 
            DefaultRootWindow(dis), 
            True, 
            GrabModeAsync, 
            GrabModeAsync, 
            CurrentTime );
    return 0;
}

int controlling(xdo_t *xdo, Display *dis){
	XEvent event;
    XKeyEvent kevent;
    Window window;

    int acc = 0;
	int endControl = False;
    int move_dist = 0;
	while (!endControl){
        XNextEvent(dis, &event);
	    switch (event.type){
            case KeyPress:
                
                kevent = *(XKeyEvent*)&event;
                move_dist = BASE_SPEED + (GROWTH_RATIO * acc);  

                switch(kevent.keycode){
                    case BUTTON:
                        xdo_get_focused_window(xdo, &window);
                        xdo_click_window( xdo, window, 1); 
                        break;
                    case BUTTON_1:
                        xdo_get_focused_window(xdo, &window);
                        xdo_click_window( xdo, window, 1); 
                        break;
                    case BUTTON_2:
                        xdo_get_focused_window(xdo, &window);
                        xdo_click_window( xdo, window, 2); 
                        break;
                    case BUTTON_3:
                        xdo_get_focused_window(xdo, &window);
                        xdo_click_window( xdo, window, 3); 
                        break;
                    case KEY_LEFT_UP:
                        move_dist = move_dist * OBLIQUE_RATE;
                        xdo_move_mouse_relative( xdo,
                                -1 * move_dist,
                                -1 * move_dist );
                        break;
                    case KEY_UP:
                        xdo_move_mouse_relative( xdo,
                                0,
                                -1 * move_dist );
                        break;
                    case KEY_RIGHT_UP:
                        move_dist = move_dist * OBLIQUE_RATE;
                        xdo_move_mouse_relative( xdo,
                                move_dist,
                                -1 * move_dist );
                        break;
                    case KEY_LEFT:
                        xdo_move_mouse_relative( xdo,
                                -1 * move_dist,
                                0 );
                        break;
                    case KEY_RIGHT:
                        xdo_move_mouse_relative( xdo,
                                move_dist,
                                0 );
                        break;
                    case KEY_LEFT_DOWN:
                        move_dist = move_dist * OBLIQUE_RATE;
                        xdo_move_mouse_relative( xdo,
                                -1 * move_dist,
                                move_dist );
                        break;
                    case KEY_DOWN:
                        xdo_move_mouse_relative( xdo,
                                0,
                                move_dist );
                        break;
                    case KEY_RIGHT_DOWN:
                        move_dist = move_dist * OBLIQUE_RATE;
                        xdo_move_mouse_relative(
                                xdo,
                                move_dist,
                                move_dist );
                        break;
                    case SCROLL_UP:
                        xdo_get_focused_window(xdo, &window);
                        xdo_click_window( xdo, window, 4); 
                        break;
                    case SCROLL_DOWN:
                        xdo_get_focused_window(xdo, &window);
                        xdo_click_window( xdo, window, 5); 
                        break;
                    case KEY_ESC:
                        endControl = True;
                        break;

                }
                break;

				case KeyRelease:
                	kevent = *(XKeyEvent*)&event;
					if (XEventsQueued(dis, QueuedAfterReading)){
						XEvent nev;
						XPeekEvent(dis, &nev);
						// Holding the key
						if (nev.type == KeyPress && nev.xkey.time == kevent.time &&
							nev.xkey.keycode == kevent.keycode){
							if(isMovement(kevent.keycode)){
								acc += 1;
								if( (BASE_SPEED + (acc*GROWTH_RATIO)) > MAX_SPEED ) acc -= 1; 
							}
						}
						
					}
					// Key released
                    else {
				    	acc = 0;
				    }

        }
        fflush(stdout);
	}
    return 0;
}

int endCapture(xdo_t *xdo, Display *dis){
    XAllowEvents(
            dis,
            SyncKeyboard,
            CurrentTime
            );
    return 0;
}

int main(int argc, char *argv[]){

    Display *dis;
    xdo_t *xdo;

    if((dis = XOpenDisplay(NULL)) == NULL) {
       perror(argv[0]);
       exit(1);
    }

    xdo = xdo_new_with_opened_display(dis, "rdtc", True);
    startCapture(xdo, dis);
    controlling(xdo, dis);
    endCapture(xdo, dis);
    return 0;
};


