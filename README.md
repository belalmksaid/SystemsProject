# SystemsProject


1) Read Data
2) Mergesort
3) Output Sorted Data

Data format:
class datarow:
	cell[] cells

class cell:
	char[] str_datum
	char data_type
	int num_datum
	bool is_empty

1) Read Data
	Get header, data type for header
	Get number of columns
	Create an array of data -> datarow[] data
	
	function: split_by_comma(char* line)
		input: string line
		output string[] data between commas, trimmed
	function: get_cells(char** pre_cell_data)
		input: output of split by comma
		output: a data_row 

2) Mergesort
	Input: datarow[] data
	Output: datarow[] sorted_data

3) Output sorted data...

