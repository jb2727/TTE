#ifndef SCREEN_H_
#define SCREEN_H_

#include "TextBuffer.h"
#include "Storage.h"


void print_buffer(int y_bottom, int x_left);
void user_input_text(int curs_y, int curs_x, char user_input);
void verticle_screen_scroll_down(int curs_y, int y_max_screen);
void verticle_screen_scroll_up(int curs_y, int y_max_screen);
void horizontal_screen_scroll_right(int cur_x, int x_max_screen);
void horizontal_screen_scroll_left(int cur_x, int x_max_screen);
void user_delete_char(int curs_y, int curs_x);

int min(int x, int y);
int max(int x, int y);

#endif /* defined(SCREEN_H_) */