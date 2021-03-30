/** 
 * Screen.c
 * Holds all of the functions responsible for manipulating the 
 * apperance of the main window and the users interaction with it
 */

#include "Screen.h"
#include "TextBuffer.h"



/** next two variables contols what part of the file the screen is viewing **/

//if the screen is at the top of the file, then y_bottom_offset is = vertical length of screen
//if the screen is at the bottom, then this is equal to the number of rows in the text file
int y_bottom_offset;
//how far away from the left edge of the file the screen is viewing
int x_left_offset; 

/**
 * implements character deletion
 */
void user_delete_char(int curs_y, int curs_x){
    x_remove_node(curs_y, curs_x-1);
    move(curs_y, curs_x-1);
    print_buffer(y_bottom_offset,x_left_offset);
}

/**
 * implements character input
 */
void user_input_text(int curs_y, int curs_x, char user_input){
    int y_max = getmaxy(stdscr);
    int x_max = getmaxx(stdscr);
    int x_list_length = x_find_end(y_node_find(curs_y))->index;
    //if user attempts to add text anywhere that's not next to end of the current line, 
    //move their cursor to the end of the of the current line then add text
    if (curs_x+x_left_offset > x_list_length){
        move(curs_y,x_list_length-x_left_offset);
        curs_x = x_list_length-x_left_offset;
    }
    //insert text into the linked list before the cursor, and then move the cursor forward
   
    /**
    curs_y+y_buttom_offset-y_max and curs_x+x_left_offset 
    finds the cursor position relative to the screen position  
    so that the text can be inserted into the correct positon of the 2D linked list
    only using th current cursor coordinates and the screen offsets
    **/

    insert_node_before(curs_y+y_bottom_offset-y_max, curs_x+x_left_offset, user_input);
    print_buffer(y_bottom_offset, x_left_offset); //CHANGE LATER: would be much more efficient if I only repaint a single line
    move(curs_y,curs_x+1);
}

/**
 * implements screen scrolling down via down key
 */
void verticle_screen_scroll_down(int curs_y, int y_max_screen){
    y_bottom_offset = min(y_bottom_offset+1,y_find_end()->index+1);
    print_buffer(y_bottom_offset,x_left_offset);
    }

/**
 * implements screen scrolling up via up key
 */
void verticle_screen_scroll_up(int curs_y, int y_max_screen){
    y_bottom_offset = max(y_bottom_offset-1,y_max_screen);
    print_buffer(y_bottom_offset,x_left_offset);
    }

/**
 * implements screen scrolling right via right key
 */
void horizontal_screen_scroll_right(int cur_x, int x_max_screen){
    x_left_offset = x_left_offset+1;
    print_buffer(y_bottom_offset,x_left_offset);
    }

/**
 * implements screen scrolling left via left key
 */
void horizontal_screen_scroll_left(int cur_x, int x_max_screen){
    x_left_offset = max(x_left_offset-1,0);
    print_buffer(y_bottom_offset,x_left_offset);
    }

/**
 * Prints the relevant parts of the file to the current the screen
 */
void print_buffer(int y_bottom_offset, int x_left_offset){
    //old position of the cursor before the printing
    int y_curs_old = getcury(stdscr);
    int x_curs_old = getcurx(stdscr);

    int y_size = getmaxy(stdscr);
    int x_size = getmaxx(stdscr); 
    int size_of_y_list = y_find_end()->index;
    
    //it's important to clear the screen to ensure that any of the "old" characters that were on screen are no longer there
    erase(); 
    //finds the y_node that's at the top of the new screen to be printed screen, 
    //ensures that this doesn't attempt to print the contents of a y_node that doesn't exist 
    y_iterator = y_node_find(min(y_bottom_offset - y_size, size_of_y_list+1 - y_size));

    //moves the cursor to top left corner of the screen and prints each line from top to bottom and left to right
    int x_curs = 0;
    int y_curs = 0;
    move(y_curs,x_curs);

    //y is unimportant, for loop used to ensure that no more lines than the verticl screen length
    for (int y = 0; (y<=y_size-1 && y_iterator != NULL);y++){
        
        //finds the relevant part of the first file line to be printed
        struct x_node *x_iterator = x_node_find(x_left_offset, y_iterator->x_first);     
        //if the file line is too "short" to be seen on the current screen, then just print an empty line
        if (x_find_end(y_iterator)->index < x_left_offset){
            addch('\n');
        } 
        //otherwise print a number of characters from the text file equal to the either 
        //the length of remaining characters on the line or the horizontal width of the screen
        else {  
            for (int x = 0; x<x_size; x++){
                if (x_iterator == NULL){
                    break;
                }
                else{
                    //accounts for the fact that the element in the x portion of the 2D array list is an empty char and shouldn't be printed
                    if ( (x_iterator->index != -1) ){
                        addch(x_iterator->data);
                    }
                    else{
                        x--; 
                    }
                //gets the next character to be printed and moves the cursor along by one 
                x_curs++;
                x_iterator = x_iterator->x_next; 
                }
            }          
    }
    //gets the next line to be printed
    x_curs = 0;
    y_curs++;
    y_iterator = y_iterator->y_next;
    }
    //moves the cursor back to it's original position
    move(y_curs_old,x_curs_old);
    refresh(); //shouldn't need this, remove later
}

//self explantory
int min(int x, int y){
    if (y<x){
        return y;
    }
    else{
        return x;
    }
}

int max(int x, int y){
    if (y>x){
        return y;
    }
    else{
        return x;
    }
}
