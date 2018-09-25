#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdlib.h>
#include <stdio.h>


#define bool char
#define true 1

#define false 0
#define INT 'i'
#define STR 's'
#define DATE 'd'

#define TABLE_SIZE 5000

#define max(a, b) ((a) > (b) ? (a) : (b))


typedef struct {
        char* original;
        char* str_datum;
        int str_len;
        int num_datum;
        char data_type;
        bool is_empty;
} cell;

typedef struct {
        cell* cells;
        int size;
} datarow;

typedef struct {
        datarow** rows;
        char** header;
        int size;
        int max_size;
} table;

datarow* create_datarow(cell* cells, int col_count);
table* create_table();
void append(table* tab, datarow* row);

#endif
