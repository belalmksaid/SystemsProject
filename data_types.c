#include "data_types.h"

datarow create_datarow(cell* cells, int col_count) {
	datarow row;
	row.size = col_count;
	row.cells = cells;
	return row;
}

table* create_table() {
	table* tab = (table*)malloc(sizeof(table));
	tab->rows = (datarow*)malloc(TABLE_SIZE * sizeof(datarow));
	tab->max_size = TABLE_SIZE;
	tab->size = 0;
	return tab;
}

void append(table* tab, datarow* row) {
	if(tab->size < tab->max_size) {
		tab->rows[tab->size] = *row;
		tab->size++;
	}
	else {
		datarow* temp = tab->rows;
		tab->max_size *= 2;
		tab->rows = (datarow*)malloc(tab->max_size * sizeof(datarow));
		int i = 0;
		for(i = 0; i < tab->size; i++)
			tab->rows[i] = temp[i];
		free(temp);
		append(tab, row);
	}
}
