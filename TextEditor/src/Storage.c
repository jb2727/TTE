/** 
 * Storage.c
 * Holds all the functions responsible for reading from and saving to files
 */

#include "Storage.h"
#include "TextBuffer.h"


/**
 * This function should be merged into create buffer unless I decide to 
 * Implement support for opening a new file during runtime
 */
void create_buffer(char *filelocation){
    struct y_node *root_node = y_list_init();
    read_file_into_buffer(filelocation, root_node);
}

/**
 * Finds a file with name filelocation and reads it's contents into memory
 */
void read_file_into_buffer(char *filelocation, struct y_node *root_node){
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    size_t line_size;

    FILE *read_file = fopen(filelocation, "r");
    if (read_file == NULL){
        //create new file - not yet implemented
    }

    //creates new text lines in memory and fills them with the contents of the file line by line
    do {
        struct y_node *end = y_find_end();

        if (end->x_first != NULL){
            end = y_node_insert(end);
        }
    
        line_buf = NULL;
        line_size = getline(&line_buf, &line_buf_size, read_file);
        read_line_into_buffer(line_buf, end);
    } while (!feof(read_file));
}

/**
 * creates new columns in memory for each line and puts the text from the file into them
 */
void read_line_into_buffer(char *line, struct y_node *end){
    
    //NOTE: This creates an additional x_node which is not needed to store text
    //The reason for this is because the y axis of the linked list and the x axis are two different types
    //Other functons in TextBuffer.c which insert text into the file require that the x_node pointer to the node before the desired insertion
    //address is found, which will causes issue if a user attempts to insert text into the first node in a row which is always
    //pointed to by a y_node, therefore creating an extra x_node which is inacessiable to the user resolves this problem neatly
    //at the cost of a very insignificant amount of memory and access time.
    struct x_node *prev_node = x_node_insert(x_list_init(end)); 
    
    //sets the text of a node, then creates a new node that is pointed to by it and repeat until 
    //there is no more in a line to be placed into memory from the file 
    prev_node->data = line[0];
    for (int i = 1; i<strlen(line);i++){
        struct x_node *cur_node = x_node_insert(prev_node);
        cur_node->data = line[i];
        prev_node = cur_node;
    }
    
}



