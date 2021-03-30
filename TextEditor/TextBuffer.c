/**
 * Function responsible for "holding" the text during editing
 * The text is stored in a linked list structure where the 
 * x axis represents the the column and the y axis represents the row/line number;
 */ 

/** 
 * NOTES TO SELF:
 * should I use calloc instead? It's slower (which is a concern given my appoach)
 * but it init's all values to zero which might fixed some weird bugs 
 * such as free()ing a location and then malloc()ing it again
 * 
 */ 

#include "TextBuffer.h"


struct y_node *y_head = NULL;
struct y_node *y_iterator = NULL;


/**
 * Y LINKED LIST FUNCTIONS
 */ 

//creates the firt node
struct y_node *y_list_init(){
    struct y_node *link = (struct y_node*) malloc(sizeof (struct y_node));
    y_head = link;
    link->y_next = NULL;
    link->index = 0;
    return link;
}

//inserts a node infront of the arg node
struct y_node *y_node_insert(struct y_node *node){
    struct y_node *link = (struct y_node*) malloc(sizeof (struct y_node));
    link->index = node->index+1;
    link->y_next = node->y_next;
    node->y_next = link;
    //as a element has been inserted into the list, the indexes of every item "infront" of it must be shifted forward by one.
    y_node_shift(node,1);
    return link;
} 

//returns the pointer of the node that contains the desired index.
//warn
struct y_node *y_node_find(int tar_index){
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

//increments/decrements the indexes of all nodes by the direction and magnitude of the arg
//note: shift should only be 1 (increments) or -1 (decrements)
void y_node_shift(struct y_node *node, int shift){
    y_iterator = node;
    while (y_iterator->y_next != NULL){
        y_iterator->index+shift;
        y_iterator = y_iterator->y_next;
    }
    y_iterator->index+shift; 
}

bool y_remove_node(int y){
    struct y_node* node_behind = y_node_find(y-1);
    struct y_node* node_tobe_removed = y_node_find(y);
    node_behind->y_next = node_tobe_removed->y_next;
    if (node_behind == NULL || node_tobe_removed == NULL){
        return false;
    }
    node_behind->y_next = node_tobe_removed->y_next;
    for (int x = 0; true; x++){
        if (!x_remove_node(node_tobe_removed->index, x)){
            break;
        }
    }
    y_node_shift(node_tobe_removed,-1);
    node_tobe_removed->index = ' ';
    node_tobe_removed->y_next = NULL; 
    
    
    free(node_tobe_removed);
    return true;
}

struct y_node *y_find_end(){
    y_iterator = y_head;
    while (y_iterator->y_next != NULL){
        y_iterator = y_iterator->y_next;
    }
    
    return y_iterator;
}

/**
 * X LINKED LIST FUNCTIONS
 */
 
//creates the firt node 
struct x_node *x_list_init(struct y_node *index){
    struct x_node *link = (struct x_node*) malloc(sizeof (struct x_node));
    index->x_first = link;
    link->index = 0;
    link->x_next = NULL;
    link->data = ' ';
    return link;
 }

//inserts a new node infront of the arg node
struct x_node *x_node_insert(struct x_node *node){
    struct x_node *link = (struct x_node*) malloc(sizeof (struct x_node));
    link->index = node->index+1;
    link->x_next = node->x_next;
    link->data = ' ';
    node->x_next = link;
    //as a element has been inserted into the list, the indexes of every item "infront" of it must be shifted forward by one.
    x_node_shift(node,1); 
    return link;
}

//parent node refers to the the y_node that the linked list that this node belongs too
//is attached too 
struct x_node *x_node_find(int tar_index, struct x_node *iterator){
    //struct x_node* iterator = parent_node->x_first;
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

//increments/decrements the indexes of all nodes by the direction and magnitude of the arg inclusive
//note: shift should only be 1 (increments) or -1 (decrements)
void x_node_shift(struct x_node *node, int shift){
    struct x_node *iterator = node;
    while (iterator->x_next != NULL){
        iterator->index+shift;
        iterator = iterator->x_next;
    }
    iterator->index+shift; 
}

bool x_remove_node(int y, int x){
    struct x_node *node_behind = find_node(y, x-1);
    struct x_node *node_tobe_removed = find_node(y, x);
    if (node_behind == NULL || node_tobe_removed == NULL){
        return false;
    }
    
    node_behind->x_next = node_tobe_removed->x_next;
    x_node_shift(node_tobe_removed,-1);
    //just to get potentially get rid weird of any weird bugs
    //might just be a waste of CPU time
    node_tobe_removed->data = ' ';
    node_tobe_removed->index = -1;
    node_tobe_removed->x_next = NULL;
    free(node_tobe_removed); 
    return true;
}

/**
 * Functions that operate on both x and y list
 */ 

//reads a char from the linked list structure
char get_char(int y, int x){
    struct x_node *node = find_node(y, x);
    if (node != NULL){
        return ' ';
    }
    else{
        return node->data;
    }
}

//inputs a char into the linked list struture
//returns true if the char could be inputted, false if the node wasn't found
bool change_char(char input, int y, int x){
    struct x_node *node = find_node(y, x);
    if (node == NULL){
        return false;
    }
    else{
        node->data = input;
        return true;
    }
}

//the y_node_find and x_node_find functions wrapped into one
struct x_node *find_node(int y, int x){
    struct x_node *header = y_node_find(y)->x_first;
        if (header != NULL){
            struct x_node* node = x_node_find(x, header);
            if (node != NULL){
                return node;
            }
        }
        return NULL;
}

struct x_node *x_find_end(struct y_node *root){
    struct x_node *iterator = root->x_first;
    while (1){
        if (iterator->x_next != NULL){
            iterator = iterator->x_next;
        }else{
            return iterator;
        }
    }
        
}

struct x_node *find_node_before(int y, int x){
    struct y_node *y_pointer = y_node_find(y);
    struct x_node *node_before = y_pointer->x_first;
    while(1){
        if (node_before->x_next == NULL){
            return NULL;
        }
        else{
            if (node_before->index == x){
                return node_before;
            }
            else{
                node_before = node_before->x_next;
            }
        }  
    }
}

void insert_node_before(int y, int x, char input){
    //need to add if case incase the node is at 0;
    struct x_node *node = find_node_before(y, x);
    struct x_node *new_node = (struct x_node*) malloc(sizeof(struct x_node));
    new_node->data = input;
    new_node->index = node->index;
    new_node->x_next = node;
    node->x_next = new_node;
    x_node_shift(new_node, 1);
}

