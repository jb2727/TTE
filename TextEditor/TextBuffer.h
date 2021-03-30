#ifndef TEXTBUFFER_H_
#define TEXTBUFFER_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>

extern struct y_node *y_head;// = NULL;
extern struct y_node *y_iterator;// = NULL;

struct y_node {
    int index;
    struct y_node *y_next;
    struct x_node *x_first; //head of the x_list!
};

struct x_node {
    char data;
    int index;
    //struct y_node* x_head;
    struct x_node *x_next;
};

struct y_node *y_list_init();
struct y_node *y_node_insert(struct y_node *node);
struct y_node *y_node_find(int tar_index);
void y_node_shift(struct y_node *node, int shift);
bool y_remove_node(int y);
struct y_node *y_find_end();

struct x_node *x_list_init(struct y_node *index);
struct x_node *x_node_insert(struct x_node *node);
void x_node_shift(struct x_node *node, int shift);
struct x_node *x_node_find(int tar_index, struct x_node *iterator);
bool x_remove_node(int y, int x);
struct x_node *x_find_end(struct y_node *root);

struct x_node *find_node(int y, int x);
char get_char(int x, int y);
bool change_char(char input, int y, int x);
struct x_node *find_node_before(int y, int x);
void insert_node_before(int y, int x, char input);

#endif /* defined(TEXTBUFFER_H_) */