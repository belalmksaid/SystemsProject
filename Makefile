all: simpleCSVsort

simpleCSVsort: mergesort.c stringproc.c data_types.c
	gcc -g -Wall -Werror -fsanitize=address mergesort.c stringproc.c data_types.c simpleCSVsorter.c -o simpleCSVsorter 

mergesort: mergesort.c mergetest.c
	gcc -Wall -Werror -fsanitize=address -g mergesort.c -g data_types.c -o mergetest 
	
clean: mergesort
	rm -f mergetest
