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
void print_row(datarow* row)

char get_type(char* val);

//mergesort
int compare(datarow A, datarow B, int index);

datarow * merge(datarow * A, int nA, datarow * B, int nB, int index);

datarow * sort(datarow * data, int ndata, int index);

datarow * mergesort(datarow * data, int index, int nrows );


// implementation
char get_type(char* val) {
	if(strcmp(val, "color") == 0 || strcmp(val, "director_name") == 0 || strcmp(val, "actor_2_name") == 0 || strcmp(val, "genres") == 0 || strcmp(val, "actor_1_name") == 0 || strcmp(val, "movie_title") == 0 || strcmp(val, "actor_3_name") == 0 || strcmp(val, "plot_keywords") == 0  || strcmp(val, "movie_imdb_link") == 0 || strcmp(val, "language") == 0 || strcmp(val, "country") == 0 || strcmp(val, "content_rating") == 0) {
		return STR;
	}
	else if(strcmp(val, "duration") == 0)
		return INT;
	return INT;
}

void print_row(datarow* row) {
	int i = 0;
	for(i = 0; i < row->size; i++) {
		printf("%s", row->cells[i].original);
		if(i < row->size - 1) printf(",");
	}

	printf("\n");
}

void print_header(char** vals, int n) {
	int i = 0;
	for(i = 0; i < n; i++) {
		printf("%s", vals[i]);
		if(i < n - 1) printf(",");
	}
	printf("\n");
}

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

char** split_by_comma(char* line, int* len) {
	int i = 0, prev_i = 0;
	int count = 1;
	int max_size = 1;
	bool inside_quote = false;
	int line_length = 0;
	while(line[i] != '\0' && line[i] != '\n') {
		if(line[i] == '"')
			inside_quote = inside_quote ? false : true;
		if(line[i] == ',' && inside_quote == false) {
			count++;
			max_size = max(max_size, i - prev_i);
			prev_i = i;
		}
		i++;
		line_length++;
	}
	inside_quote = false;
	char** words = (char**)malloc(count * sizeof(char*));
	for(i = 0; i < count; i++) {
		words[i] = (char*)malloc(max_size * sizeof(char));
		words[i][0] = '\0';
	}
	int curr_word = 0;
	int curr_i = 0;
	for(i = 0; i < line_length; i++) {
		if(line[i] == '"')
        	       	inside_quote = inside_quote ? false : true;
		if(line[i] == ',' && inside_quote == false) {
			words[curr_word++][curr_i] = '\0';
			curr_i = 0;
		}
		else {
			words[curr_word][curr_i++] = line[i];
		}
	}
	*len = count;
	return words;
}


cell* get_cells(char** pre_cell, char data_type, int index, int len) {
	int i = 0;
	cell* cells = (cell*)malloc(len * sizeof(cell));
	for(i = 0; i < len; i++) {
		cells[i].original = pre_cell[i];
		cells[i].is_empty = pre_cell[i][0] == '\0' ? true : false;
		if(cells[i].is_empty) {
			cells[i].str_len = 0;
		}
		if(i == index) {
			cells[i].data_type = data_type;
			int st = 0;
			int end = 0;
			while(pre_cell[i][st] == ' ' || pre_cell[i][st] == '\t' || pre_cell[i][st] == '"') st++;
			while(pre_cell[i][end] != '\0') end++;
			end--;
			while(end > -1 && (pre_cell[i][end] == ' ' || pre_cell[i][end] == '\t' || pre_cell[i][end] == '"')) end--;
			if(end <= st) cells[i].is_empty = true;
			else {
				cells[i].is_empty = false;
				int j = 0;
				cells[i].str_datum = (char*)malloc((end - st + 2) * sizeof(char));
				for(j = st; j <= end; j++)
					cells[i].str_datum[j - st] = pre_cell[i][j];
				cells[i].str_datum[j - st] = '\0';
				cells[i].str_len = end - st + 1;
				if(data_type == INT)
					cells[i].num_datum = atoi(cells[i].str_datum);
			}
		}
	}
	return cells;
}


