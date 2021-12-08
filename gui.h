#ifndef GUI_H
#define GUI_H

#include <time.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

typedef enum
{
    BLACK, RED,
    GREEN, BLUE, WHITE
} Color;

typedef enum
{
     KEY_W = 119, KEY_UP =    72,
     KEY_S = 115, KEY_DOWN =  80,
     KEY_A =  97, KEY_LEFT =  75,
     KEY_D = 100, KEY_RIGHT = 77,
    KEY_ESC = 27, KEY_ENTER = 13
} KeyButton;

void delay(time_t d);
void set_color(Color c);
void goto_xy(int x, int y);
void clear_screen();
KeyButton get_key();
bool key_hit();
void set_cursor_visible(WINBOOL visible);
void set_window_size(int width, int height);
void set_window_title(const char* text);

#endif // GUI_H