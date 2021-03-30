/**
 * TextBuffer.c
 * Function responsible for "holding" the text during editing
 * The text is stored in a 2D linked list structure where the 
 * x axis represents the columns and the y axis represents the row/line number;
 */ 

#include "TextBuffer.h"

struct y_node *y_head = NULL;
struct y_node *y_iterator = NULL;


/**
 * Y LINKED LIST FUNCTIONS
 */ 

/**
 * creates the firt node in the linked list structure so that others may be added to it in the future
 */
struct y_node *y_list_init(){
    struct y_node *link = (struct y_node*) malloc(sizeof (struct y_node));
    y_head = link;
    link->y_next = NULL;
    link->index = 0;
    return link;
}

/**
 * inserts a node infront of the arg node
 */ 
struct y_node *y_node_insert(struct y_node *node){
    struct y_node *link = (struct y_node*) malloc(sizeof (struct y_node));
    link->index = node->index+1;
    link->y_next = node->y_next;
    node->y_next = link;
    //as a element has been inserted into the list, the indexes of every item "infront" of it must be shifted forward by one.
    y_node_shift(node,1);
    return link;
} 

/**
 * returns the pointer of the node that contains the desired index (position).
 */
struct y_node *y_node_find(int tar_index){
    y_iterator = y_head;
    while(1){
        if (y_iterator->index == tar_index){
            return y_iterator;
        }
        else if (y_iterator->y_next == NULL){ //end of list was reach without finding desired node
            return NULL; 
        }
        else {
            y_iterator = y_iterator->y_next;
        }
    }
}

/**
 * increments/decrements the indexes of all nodes by the direction and magnitude of the arg
 */
//NOTE: shift should only be 1 (increments) or -1 (decrements), implement argument checking in future
void y_node_shift(struct y_node *node, int shift){
    y_iterator = node;
    while (y_iterator->y_next != NULL){
        y_iterator->index+shift;
        y_iterator = y_iterator->y_next;
    }
    y_iterator->index+shift; 
}

/**
 * removes a column from the linked list structure, also automatically removes all x nodes connected the y node
 * this function will also adjust the pointers of the other elements in the y list to ensure that no broken connections occur
 */
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
    link->index = -1;
    link->x_next = NULL;
    link->data = ' ';
    return link;
 }

//inserts a new node infront of the arg node
struct x_node *x_node_insert(struct x_node *node){
    struct x_node *link = (struct x_node*) malloc(sizeof (struct x_node));
    link->index = node->index;
    link->x_next = node->x_next;
    link->data = ' ';
    node->x_next = link;
    //as a element has been inserted into the list, the indexes of every item "infront" of it must be shifted forward by one.
    x_node_shift(link,1); 
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
        iterator->index = iterator->index+shift;
        iterator = iterator->x_next;
    }
    iterator->index = iterator->index+shift; 
}

//removes a x_node from the linked list structure, also automatically adjusts the pointers of previous node to 
//ensure that no part of the x_list is disconnected from the rest of the data structure.
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

/**
 * returns a pointer to the end a row
 */
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

/**
 * find the node before the current argument coordinates, implemented due to the hidden node problem
 * mentiond in storage.c read_line_into_buffer
 */
struct x_node *find_node_before(int y, int x){
    struct y_node *y_pointer = y_node_find(y);
    struct x_node *node_before = y_pointer->x_first;
    while(1){
        if (node_before->x_next == NULL){
            return NULL;
        }
        else{
            if (node_before->x_next->index == x){
                return node_before;
            }
            else{
                node_before = node_before->x_next;
            }
        }  
    }
}

/**
 * Insert text before the argument coordinates, usually used to during text insertion since text is usually added BEFORE
 * The current coordinates of the cursor in nearly all text editors, and I'd like to maintain this standard
 */
void insert_node_before(int y, int x, char input){
    struct x_node *node = find_node_before(y, x);
    struct x_node *new_node = (struct x_node*) malloc(sizeof(struct x_node));
    new_node->data = input;
    //-1 because x_node_shift will increment it by 1 anyway, the reason why I did this instead of just setting it to 0 
    //and incrementing the nodes after it is in case new_node points to NULL
    new_node->index = node->x_next->index-1; 
    new_node->x_next = node->x_next;
    node->x_next = new_node;
    x_node_shift(new_node, 1); 
}

