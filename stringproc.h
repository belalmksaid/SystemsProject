#ifndef STRING_PROC_H
#define STRING_PROC_H

#include "data_types.h"

char** split_by_comma(char* line, int* len);

cell* get_cells(char** pre_cell, int len);

#endif
