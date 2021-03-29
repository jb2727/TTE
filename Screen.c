#include "Screen.h"

//tracks what y coord of the bottom of screen the program is on


void print_buffer(int y_bottom, int x_left){
    int y_curs_old = getcury(stdscr);
    int x_curs_old = getcurx(stdscr);
    int y_size = getmaxy(stdscr);
    int x_size = getmaxx(stdscr); 
    int size_of_y_list = y_find_end()->index;
    erase();
    y_iterator = y_node_find(min(y_bottom - y_size+1, size_of_y_list));
    int x_curs = 0;
    int y_curs = 0;
    move(y_curs,x_curs);

    for (int i = 0; (i<=y_size-1 && y_iterator != NULL);i++){
        int x_print_iterator = 0;
        struct x_node *x_iterator = x_node_find(x_left, y_iterator->x_first);//y_iterator->x_first;
        /**
        if (y_iterator->x_first->data = '\n'){
            addch('\n');
        }
        **/
        if (x_find_end(y_iterator)->index < x_left){
            addch('\n');
        } else {  
        while (x_iterator != NULL && (x_iterator->index >= x_left && x_iterator->index < x_size+x_left)){
            addch(x_iterator->data);
            x_curs++;
            x_iterator = x_iterator->x_next; 
        }   
        }          
        x_curs = 0;
        y_curs++;
        y_iterator = y_iterator->y_next;
    }
    move(y_curs_old,x_curs_old);
    refresh();

}

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