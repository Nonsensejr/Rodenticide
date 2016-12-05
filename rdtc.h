#define BUTTON 39 
#define BUTTON_1 10
#define BUTTON_2 11
#define BUTTON_3 12
#define SCROLL_UP 27
#define SCROLL_DOWN 42 
#define KEY_LEFT_UP 24
#define KEY_UP 25
#define KEY_RIGHT_UP 26 
#define KEY_LEFT 38 
#define KEY_RIGHT 40
#define KEY_LEFT_DOWN 52
#define KEY_DOWN 53
#define KEY_RIGHT_DOWN 54 
#define KEY_ESC 9 
#define BASE_SPEED 4 
#define GROWTH_RATIO 2 
#define OBLIQUE_RATE 0.7
#define MAX_SPEED 30

const int MOVEMENT_KEYS[9] = { 
    KEY_LEFT_UP,
    KEY_UP,
    KEY_RIGHT_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_LEFT_DOWN,
    KEY_DOWN,
    KEY_RIGHT_DOWN };

int isMovement(int keyCode);
int startCapture();
int endCapture();
int controlling();


