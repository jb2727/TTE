#ifndef STORAGE_H_
#define STORAGE_H_

#include "TextBuffer.h"

struct y_node* create_buffer(char* filelocation);
void read_file_into_buffer(char* filelocation, struct y_node* root_node);
void read_line_into_buffer(char* line);

#endif /* defined(STORAGE_H_) */
