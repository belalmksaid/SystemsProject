#include "simpleCSVsorter.h"

// implementation
char get_type(char* val) {
	if(strcmp(val, "color") == 0 || strcmp(val, "director_name") == 0 || strcmp(val, "actor_2_name") == 0 || strcmp(val, "genres") == 0 || strcmp(val, "actor_1_name") == 0 || strcmp(val, "movie_title") == 0 || strcmp(val, "actor_3_name") == 0 || strcmp(val, "plot_keywords") == 0  || strcmp(val, "movie_imdb_link") == 0 || strcmp(val, "language") == 0 || strcmp(val, "country") == 0 || strcmp(val, "content_rating") == 0) {
		return STR;
	}
	else if(strcmp(val, "duration") == 0)
		return INT;
	return FLOAT;
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
//		if(i == index1 || i==index2 || i==index3) {
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
				if(data_type == INT || data_type == FLOAT) {
					cells[i].num_datum = atoi(cells[i].str_datum);
//				else if(data_type == FLOAT)
					cells[i].f_datum = atof(cells[i].str_datum);
//				}
			}
		}
	}
	return cells;
}


int main(int argc, char* argv[]) {
	int i = 1;
	char sort_type = INT;
	char buff[BUFSIZ];
	char *read = fgets(buff, sizeof buff, stdin);
	int no_of_cols = 0;
	char** headers = split_by_comma(buff, &no_of_cols);
	int dur_ind, imdb_ind, gross_ind;
	for(i = 0; i < no_of_cols; i++) {
		if(!strcmp(headers[i], "duration")) {
			dur_ind = i;
		}
		else if(!strcmp(headers[i], "imdb_score")){
			imdb_ind = i;
		}
		else if(!strcmp(headers[i], "gross")){
			gross_ind = i;
		}
	}
	table* main_table = create_table();
	main_table->header = headers;
	read = fgets(buff, sizeof buff, stdin);
	while(read != NULL) {
		int nc = 0;
		char** split_line = split_by_comma(buff, &nc);
		cell* cells = get_cells(split_line, sort_type, dur_ind, nc);
		datarow row = create_datarow(cells, nc);
		append(main_table, &row); 
		read = fgets(buff, sizeof buff, stdin);
	}
	float long_score = 0;
	double long_gross = 0;
	float short_score = 0;
	double short_gross = 0;
	int nlong_s = 0;
	int nlong_g = 0;
	int nshort_s = 0;
	int nshort_g = 0;
	int nmins = atoi(argv[1]);
	for(i = 0; i < main_table->size; ++i){
		if(main_table->rows[i].cells[dur_ind].is_empty == true){
			continue;
		}
		if(main_table->rows[i].cells[dur_ind].num_datum >= nmins){
			if(main_table->rows[i].cells[imdb_ind].is_empty == false) {
				long_score += main_table->rows[i].cells[imdb_ind].f_datum;
				nlong_s++;
			}
			if(main_table->rows[i].cells[gross_ind].is_empty == false) {
				long_gross += main_table->rows[i].cells[gross_ind].num_datum;
				nlong_g++;
			}
		}
		else {
			if(main_table->rows[i].cells[imdb_ind].is_empty == false){
				short_score += main_table->rows[i].cells[imdb_ind].f_datum;
				nshort_s++;
			}
			if(main_table->rows[i].cells[gross_ind].is_empty == false){
				short_gross += main_table->rows[i].cells[gross_ind].num_datum;
				nshort_g++;
			}
		}
	}
//	printf("nlong_s: %d nlong_g: %d nshort_s: %d nshort_g: %d longscore: %f shortscore: %f longgross: %f shortgross:%f\n", nlong_s, nlong_g, nshort_s, nshort_g, long_score, short_score, long_gross, short_gross);
	long_score /= nlong_s;
	short_score /= nshort_s;
	long_gross /= nlong_g;
	long_gross /= 1000000;
	short_gross /= nshort_g;
	short_gross /= 1000000;
	printf("Movies >= nmins minutes in duration had an average score of %f, with an average gross of $%f million, while movies shorter than nmins minutes had an average score of %f, with an average gross of $%f million.\n", long_score, long_gross, short_score, short_gross);
	return 0;
}
