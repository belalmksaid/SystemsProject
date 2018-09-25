#include <stdlib.h>
#include <stdio.h>


#define bool char
#define true 1

#define false 0
#define INT 'i'
#define STR 's'

#define TABLE_SIZE 5000

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


datarow* create_datarow(cell* cells, int col_count) {
	datarow* row = (datarow*)malloc(sizeof(datarow));
	row->size = col_count;
	return row;
}

table* create_table() {
	table* tab = (table*)malloc(sizeof(table));
	tab->rows = (datarow**)malloc(TABLE_SIZE * sizeof(datarow*));
	tab->max_size = TABLE_SIZE;
	tab->size = 0;
	return tab;
}

void append(table* tab, datarow* row) {
	if(tab->size < tab->max_size) {
		tab->rows[tab->size] = row;
		tab->size++;
	}
	else {
		perror("not implemented");
	}
}
