#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include "Storage.h"
#include "Screen.h"

//global control variables



//when true, continue recieving inputs from user, when false, end program.
bool main_control_loop = true; 
//buffer for storing text input before it is added to linked list structur
char* buffer[1024];
//
int y_bottom;
int x_left;


void user_input_text(int curs_y, int curs_x, char user_input){
    /**
    struct y_node *y_pointer = y_node_find(curs_y);
    struct x_node *x_pointer = x_node_find(curs_x, y_pointer->x_first);
    x_node_insert(x_pointer);
    change_char(user_input, curs_y, curs_x);
    move(curs_y, curs_x+1);
    **/
    int y_max = getmaxy(stdscr);
    int x_max = getmaxx(stdscr);
    insert_node_before(curs_y+y_bottom-y_max, curs_x+x_left, user_input);
    /**
    struct x_node *x_pointer = find_node(curs_y+y_bottom-y_max+1, curs_x+x_left);
    x_node_insert(x_pointer);
    x_pointer->x_next->data = user_input;
    **/
    

    print_buffer(y_bottom, x_left); //would be much more efficient if I only repaint a single line
}

void verticle_screen_scroll_down(int curs_y, int y_max_screen){
    y_bottom = min(y_bottom+1,y_find_end()->index+1);
    print_buffer(y_bottom,x_left);
        
    }

void verticle_screen_scroll_up(int curs_y, int y_max_screen){
    y_bottom = max(y_bottom-1,y_max_screen);
    print_buffer(y_bottom,x_left);
        
    }

void horizontal_screen_scroll_right(int cur_x, int x_max_screen){
    x_left = x_left+1;
    print_buffer(y_bottom,x_left);
    }

void horizontal_screen_scroll_left(int cur_x, int x_max_screen){
    x_left = max(x_left-1,0);
    print_buffer(y_bottom,x_left);
    }

//recieves the user input and then sends it to appropiate function
void handle_input(int input){
    int curs_y, curs_x ; //positions of the cursor
    getyx(stdscr, curs_y, curs_x); 
    int y_max_screen = getmaxy(stdscr);
    int x_max_screen = getmaxx(stdscr); 
    switch(input) {
        case 27 :
            printw("%s", "HELLO");
            main_control_loop = false;
            break;
        case KEY_DOWN : 
            if (curs_y >= y_max_screen-1){
                verticle_screen_scroll_down(curs_y, y_max_screen);
            }
            else{
                move(curs_y+1,curs_x);
            }

            break;
        case KEY_UP :
            if (curs_y == 0){
                verticle_screen_scroll_up(curs_y, y_max_screen);
            }
            else{
                move(curs_y-1,curs_x);
            }
            break;
        case KEY_LEFT : 
            if (curs_x == 0){
                horizontal_screen_scroll_left(curs_x, x_max_screen);
            }
            else{
                move(curs_y, curs_x-1);
            }
            break;
        case KEY_RIGHT : 
                //move(curs_y, curs_x+1);
            if (curs_x >= x_max_screen-1){
                horizontal_screen_scroll_right(curs_x, x_max_screen);
            }
            else{
                move(curs_y,curs_x+1);
            }
            break;
        case KEY_DC : 

            break;
        case KEY_COPY : //ctrl + c

            break;
        case KEY_SAVE : //ctrl + s 

            break;
        default : 
            user_input_text(curs_y, curs_x, input);
    }
}

int main(int argc, char *argv){

    create_buffer("plan.txt");
    //initializes the standard screen and control variables
    int usr_input;
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    raw();
    
    y_bottom = getmaxy(stdscr);
    x_left = 0;
    print_buffer(y_bottom, x_left);
    

    //main program loop, wait until user input and then do something based on that input!
    while (main_control_loop){

        refresh();
        usr_input = getch();
        handle_input(usr_input);

    }

    endwin();
    return EXIT_SUCCESS;
}

