#include "stringproc.h"


int main(int argc, char* argv[]) {
	int count = 0;
	char** test1 = split_by_comma("a,b,c,d,\"eee, kk\",,13", &count);
	cell* cells1 = get_cells(test1, INT, 6, 7);
	int i = 0;
	for(i = 0; i < count; i++)
		printf("%s\n", test1[i]);
	printf("number, %d\n", cells1[6].num_datum);
	return 0;
}
