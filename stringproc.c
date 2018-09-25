#include "data_types.c"

char** split_by_comma(char* line, int* len) {
	int i = 0, prev_i = 0;
	int count = 1;
	int max_size = 0;
	bool inside_quote = false;
	while(line[i] != EOF && line[i] != '\n') {
		if(line[i] == '"')
			inside_quote = inside_quote ? false : true;
		if(line[i] == ',' && inside_quote == false) {
			count++;
			max_size = max(max_size, i - prev_i + 1);
			prev_i = i;
		}
		i++;
	}
	inside_quote = false;
	int curr_i = 0;
	int curr_word = 0;
	char** words = (char**)malloc(count * sizeof(char*));
	i = 0;
	for(i = 0; i < count; i++) {
		words[i] = (char*)malloc(max_size * sizeof(char));
		words[i][0] = '\0';
	}
	i = 0;
	while(line[i] != EOF && line[i] != '\n') {
		if(line[i] == '"')
                	inside_quote = inside_quote ? false : true;
		if(line[i] == ',' && inside_quote == false) {
			words[curr_word][curr_i + 1] = '\0';
			curr_word++;
		}
	}
}


cell* get_cells(char** pre_cell, int len) {
}
