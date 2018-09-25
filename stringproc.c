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


cell* get_cells(char** pre_cell, int len) {
	return NULL;
}
