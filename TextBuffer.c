#include "TextBuffer.h"

struct y_node* y_head = NULL;
struct y_node* y_iterator = NULL;

struct y_node {
    int index;
    struct y_node* y_next;
    struct x_node* x_first; //head of the x_list!
};

struct x_node {
    char data;
    int index;
    //struct y_node* x_head;
    struct x_node* x_next;
};

/**
 * Y LINKED LIST FUNCTIONS
 */ 

//creates the firt node
struct y_node* y_list_init(){
    struct y_node* link = (struct y_node*) malloc(sizeof (struct y_node));
    y_head = link;
    link->y_next = NULL;
    link->index = 0;
}

//inserts a node infront of the arg node
struct y_node* y_node_insert(struct y_node* node){
    struct y_node* link = (struct y_node*) malloc(sizeof (struct y_node));
    link->index = node->index+1;
    link->y_next = node->y_next;
    node->y_next = link;
    return true;
} 

//returns the pointer of the node that contains the desired index.
struct y_node* y_node_find(int tar_index){
    y_iterator = y_head;
    while(1){
        if (y_iterator->index == tar_index){
            return y_iterator;
        }
        else if (y_iterator->y_next == NULL){
            return NULL;
        }
        else {
            y_iterator = y_iterator->y_next;
        }
    }
}

//increments the indexes of all nodes by the direction and magnitude of the arg
//note: shift should only be 1 or -1
void y_node_shift(struct y_node* node, int shift){
    y_iterator = node;
    while (y_iterator->y_next != NULL){
        y_iterator->index+shift;
        y_iterator = y_iterator->y_next;
    }
    y_iterator->index+shift; 
}


/**
 * X LINKED LIST FUNCTIONS
 */
 
//creates the firt node 
struct x_node*x_list_init(struct y_node* index){
    struct x_node* link = (struct x_node*) malloc(sizeof (struct x_node));
    index->x_first = link;
    link->index = 0;
    link->x_next = NULL;
    link->data = '\0';
    return link;
 }

//inserts a new node infront of the arg node
struct x_node* x_node_insert(struct x_node* node){
    struct x_node* link = (struct x_node*) malloc(sizeof (struct x_node));
    link->index = node->index+1;
    link->x_next = node->x_next;
    link->data = '\0';
    node->x_next = link;
    
    return link;
}

//parent node refers to the the y_node that the linked list that this node belongs too
//is attached too 
struct x_node* x_node_find(int tar_index, struct y_node* parent_node){
    struct x_node* iterator = parent_node->x_first;
    while(1){
        if (iterator->index == tar_index){
            return iterator;
        }
        else if (iterator->x_next == NULL){
            return NULL;
        }
        else {
            iterator = iterator->x_next;
        }
    }
}

/**
 * Functions that operate on both x and y list
 */ 

char get_char(int x, int y){

    struct x_node* header = y_node_find(y)->x_first;
    if (header != NULL){
        struct x_node* node = x_node_find(x, header);
        if (node != NULL){
            return node->data;
        }
    }
    return '/0';
}







