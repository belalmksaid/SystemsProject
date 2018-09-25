#define bool char
#define 't' true
#define 'f' false

typedef struct {
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
