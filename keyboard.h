
#define KEYBOARD_READ_PERIOD 25

void init_keyboard();
void read_keyboard(); //timer2 handler
int button_pressed(char id);
int button_released(char id);
int button_hold(char id);

