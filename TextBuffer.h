#ifndef TEXTBUFFER_H_
#define TEXTBUFFER_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct y_node* y_list_init();
struct y_node* y_node_insert(struct y_node* node);
struct y_node* y_node_find(int tar_index);
void y_node_shift(struct y_node* node, int shift);

struct x_node*x_list_init(struct y_node* index);
struct x_node* x_node_insert(struct x_node* node);
struct x_node* x_node_find(int tar_index, struct y_node* parent_node);

char get_char(int x, int y);

#endif /* defined(TEXTBUFFER_H_) */