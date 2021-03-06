#ifndef SIMPLECSVSORTER
#define SIMPLECSVSORTER

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


// define data types
#define bool char
#define true 1

#define false 0
#define INT 'i'
#define STR 's'
#define DATE 'd'
#define FLOAT 'f'

#define TABLE_SIZE 5000

#define max(a, b) ((a) > (b) ? (a) : (b))


typedef struct {
        char* original;
        char* str_datum;
        int str_len;
        int num_datum;
	float f_datum;
        char data_type;
        bool is_empty;
} cell;

typedef struct {
        cell* cells;
        int size;
} datarow;

typedef struct {
        datarow* rows;
        char** header;
        int size;
        int max_size;
} table;

datarow create_datarow(cell* cells, int col_count);
table* create_table();
void append(table* tab, datarow* row);


// string processing
char** split_by_comma(char* line, int* len);

cell* get_cells(char** pre_cell, char data_type, int index, int len);

void print_header(char** vals, int n);

// post processing
void print_row(datarow* row);

char get_type(char* val);

//mergesort
int compare(datarow A, datarow B, int index);

datarow * merge(datarow * A, int nA, datarow * B, int nB, int index);

datarow * sort(datarow * data, int ndata, int index);

datarow * mergesort(datarow * data, int index, int nrows );

#endif
