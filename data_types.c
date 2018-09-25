#include "data_types.h"

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
