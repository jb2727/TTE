#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include "Storage.h"
#include "Screen.h"

//next two variables contols what part of the file the screen is viewing

//if the screen is at the top of the file, then y_bottom_offset is = vertical length of screen
//if the screen is at the bottom, then this is equal to the number of rows in the text file
extern int y_bottom_offset; 
//how far away from the left edge of the file the screen is viewing
extern int x_left_offset; 


//when true, continue recieving inputs from user, when false, end program.
bool main_control_loop = true; 

/**
 * recieves the user input and then sends it to appropiate function
 */
void handle_input(int input){
    int curs_y, curs_x;
    getyx(stdscr, curs_y, curs_x); 
    int y_max_screen = getmaxy(stdscr);
    int x_max_screen = getmaxx(stdscr); 
    switch(input) {
        case 27 : //ESCAPE KEY
            //stop the main program loop to stop the program
            main_control_loop = false; 
            break;
        case KEY_DOWN : 
            //if the user attempts to scroll below the screen, print the text below
            if (curs_y >= y_max_screen-1){ 
                verticle_screen_scroll_down(curs_y, y_max_screen);
            }
            else{
                move(curs_y+1,curs_x);
            }
            break;
        case KEY_UP :
            //if the user attempts to scroll above the screen, print the text above
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
        case KEY_BACKSPACE: 
            user_delete_char(curs_y, curs_x);
            break;
        case KEY_COPY : //ctrl + c

            break;
        case KEY_SAVE : //ctrl + s 

            break;
        default : 
        //if not a command key, must be a character input, needs to be changed to avoid any edge cases
            user_input_text(curs_y, curs_x, input);
    }
}

int main(int argc, char *argv[]){
    //uses the first terminal argument to find a file to open/create, and then load it into memory
    create_buffer(argv[1]); 
    
    //initializes the standard screen and control variables
    int usr_input;
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    raw();
    y_bottom_offset = getmaxy(stdscr);
    x_left_offset = 0;
    //print the file text in memory to the screen 
    print_buffer(y_bottom_offset, x_left_offset);
    //main program loop, wait until user input and then do something based on that input!
    while (main_control_loop){

        refresh();
        usr_input = getch();
        handle_input(usr_input);

    }

    //closes the application
    endwin();
    return EXIT_SUCCESS;
}

