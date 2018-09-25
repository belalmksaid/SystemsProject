#include "stringproc.h"

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
