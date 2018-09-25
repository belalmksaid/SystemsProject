#include "simpleCSVsorter.h"

int main(int argc, char* argv[]) {
	if(argc < 3)
		perror("incorrect arguments");
	int i = 1;
	char* header_to_sort = NULL;
	for(i = 2; i < argc; i++) {
		if(strcmp(argv[i], "-c")) {
			i++;
			header_to_sort = argv[i];
		} 
	}
	
	char buff[BUFSIZ];
	char *read = fgets(buff, sizeof buff, stdin);
	int no_of_cols = 0;
	char** headers = split_by_comma(buff, &no_of_cols);
	int cell_index = -1;
	for(i = 0; i < no_of_cols; i++) {
		if(strcmp(headers[i], header_to_sort)) {
			cell_index = i;
			break;
		}
	}
	if(cell_index != -1) {
		table* main_table = create_table();
		main_table->header = headers;
		while(read != NULL) {
			read = fgets(buff, sizeof buff, stdin);
			int nc = 0;
			char** split_line = split_by_comma(buff, &nc);
			cell* cells = get_cells(split_line, INT, cell_index, nc);
			datarow* row = create_datarow(cells, nc);
			append(main_table, row); 
		}
	}
	return 0;
}
