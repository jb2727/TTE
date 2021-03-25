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


void verticle_screen_scroll_down(int curs_y, int max_screen){
    y_bottom = min(y_bottom + max_screen-1, y_find_end()->index);
    //printw("current screen pos: %d", getcury(stdscr));
    print_buffer(y_bottom);
        
    }



//recieves the user input and then sends it to appropiate function
void handle_input(int input){
    int curs_y, curs_x ; //positions of the cursor
    getyx(stdscr, curs_y, curs_x); 
    int max_screen = getmaxy(stdscr);
    switch(input) {
        case 27 :
            printw("%s", "HELLO");
            main_control_loop = false;
            break;
        case KEY_DOWN : 
            if (curs_y >= max_screen-1){
                verticle_screen_scroll_down(curs_y, max_screen);
            }
            else{
                move(curs_y+1,curs_x);
            }

            break;
        case KEY_UP :
            //verticle_screen_scroll(curs_y);
            move(curs_y-1, curs_x);
            
            break;
        case KEY_LEFT : 
            if (!curs_x == 0){
                move(curs_y, curs_x-1);
            }
            break;
        case KEY_RIGHT : 
                move(curs_y, curs_x+1);
            break;
        case KEY_DC : 

            break;
        case KEY_COPY : //ctrl + c

            break;
        case KEY_SAVE : //ctrl + s 

            break;
        default : 
            printw("%c", input);
    }
}

int main(int argc, char *argv){

    create_buffer("plan.txt");
    //initializes the standard screen and control variables
    int usr_input;
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    initscr();
    raw();
    y_bottom = getmaxy(stdscr)-1;
    print_buffer(y_bottom);
    

    //main program loop, wait until user input and then do something based on that input!
    while (main_control_loop){

        refresh();
        usr_input = getch();
        handle_input(usr_input);

    }
    
    


    /**
    
    //noecho();
    refresh();
    int y_cord, x_cord;
    attron(A_BOLD);
    printw("%s", "TESTESTESTESTESTETESTEETSETESTESETSEESTESTEE");
    //getyx(stdscr, y_cord, x_cord); //gets the TERMINAL CURSOR!!
    //printw("y coordinate: %d, x coordinate: %d\n", y_cord, x_cord);
    while (1)
    {
        usr_input = getch();
    }
    **/
    
   

    endwin();
    return EXIT_SUCCESS;
}

