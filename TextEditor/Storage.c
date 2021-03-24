#include "Storage.h"
#include "TextBuffer.h"

struct y_node* create_buffer(char* filelocation){
    struct y_node* root_node = y_list_init();
    read_file_into_buffer(filelocation, root_node);
}

void read_file_into_buffer(char* filelocation, struct y_node* root_node){
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    size_t line_size;
    FILE *read_file = fopen(filelocation, "r");
    if (read_file == NULL){
    //implement error handling here
    }

    do {
        //may cause issues if it overwrites the contents at NULL
        line_size = getline(&line_buf, &line_buf_size, read_file);
        read_line_into_buffer(line_buf);
    } while (feof(read_file));
    getline(&line_buf, NULL, read_file);
    read_line_into_buffer(line_buf);
}

void read_line_into_buffer(char* line){
    struct y_node* end = y_find_end();
    struct x_node* prev_node = x_list_init(end);
    prev_node->data;// = line[0];
    for (int i = 1; i<strlen(line);i++){
        struct x_node* cur_node = x_node_insert(prev_node);
        //note: may lead to a bug with incorrect index or data due to space chars
        cur_node->data = line[i];
        prev_node = cur_node;
    }
    
}