#include "Screen.h"

//tracks what y coord of the bottom of screen the program is on


void print_buffer(int y_bottom){
    //int y_curs = getcury(stdscr);
    erase();
    int y_size = getmaxy(stdscr);
    int x_size = getmaxx(stdscr); //might not need this
    int size_of_y_list = y_find_end()->index;
    y_iterator = y_node_find(min(y_bottom - y_size+1, size_of_y_list));
    int x_curs = 0;
    int y_curs = 0;
    move(y_curs,x_curs);
    for (int i = 0; (i<=y_size-1 && y_iterator != NULL);i++){
        struct x_node *x_iterator = y_iterator->x_first;
        while (x_iterator != NULL){
            addch(x_iterator->data);
            x_curs++;
            x_iterator = x_iterator->x_next; //might cause a seg fault             
        }
        x_curs = 0;
        y_curs++;
        y_iterator = y_iterator->y_next;
    }
    move(0,0);
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