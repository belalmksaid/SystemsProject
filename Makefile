all: simpleCSVsort

simpleCSVsort: mergesort.c stringproc.c data_types.c
	gcc -g -Wall -Werror -fsanitize=address mergesort.c stringproc.c data_types.c simpleCSVsorter.c -o simpleCSVsorter 
