#include <stdio.h>
#include <errno.h>
#include <string.h>


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
	if(header_to_sort) {}
	char buff[BUFSIZ];
	char *read = fgets(buff, sizeof buff, stdin);
	while(read != NULL) {
		read = fgets(buff, sizeof buff, stdin);
	}
	return 0;
}
