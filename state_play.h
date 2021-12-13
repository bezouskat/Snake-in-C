#ifndef STATE_PLAY_H
#define STATE_PLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "snake_direction.h"
#include "gui.h"
#include "settings.h"
#include "constants.h"

void draw_frame();
void draw_food(point f);
void display_score(int score);
void display_level(int level);
void show_blood(point p);
void game_over();

bool self_collision(list* s);
bool wall_collision(list* s);
bool food_collision(list* s, point f);

point generate_food(list* s);

void process_events(snake_direction* d);
void move_and_grow_snake(list* s, snake_direction d, bool* grow_snake);
void change_level(int* level, int* score);

void state_play();

#endif // STATE_PLAY_H
