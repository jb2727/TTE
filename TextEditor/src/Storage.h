#ifndef STORAGE_H_
#define STORAGE_H_

#include "TextBuffer.h"

void create_buffer(char *filelocation);
void read_file_into_buffer(char *filelocation, struct y_node *root_node);
void read_line_into_buffer(char *line, struct y_node *end);
int min(int x, int y);

#endif /* defined(STORAGE_H_) */
