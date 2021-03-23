#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>
#include "TextBuffer.h"

//global control variables

//when true, continue recieving inputs from user, when false, end program.
bool main_control_loop = true; 
//buffer for storing text input before it is added to linked list structur
char* buffer[1024];

//recieves the user input and then sends it to appropiate function
void handle_input(int input){
    int curs_y, curs_x ; //positions of the cursor
    getyx(stdscr, curs_y, curs_x); 

    switch(input) {
        case 27 :
            printw("%s", "HELLO");
            main_control_loop = false;
            break;
        case KEY_DOWN : 
                move(curs_y+1,curs_x);
            break;
        case KEY_UP :
            if (!curs_y == 0){
                move(curs_y-1, curs_x);
            }  
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

int main(){

    //initializes the standard screen and control variables
    int usr_input;
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    initscr();
    raw();

    

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

