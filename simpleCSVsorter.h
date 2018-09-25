#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "data_types.c"

char** split_by_comma(char* line, int* len);

cell* get_cells(char** pre_cell, int len);
