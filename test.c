#include "stringproc.h"


int main(int argc, char* argv[]) {
	int count = 0;
	char** test1 = split_by_comma("a,b,c,d,\"eee, kk\",,f", &count);
	int i = 0;
	for(i = 0; i < count; i++)
		printf("%s\n", test1[i]);
	return 0;
}
