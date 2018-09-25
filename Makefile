all: simpleCSVsort

simpleCSVsort: mergesort.c stringproc.c data_types.c
	gcc -g -Wall -Werror -fsanitize=address mergesort.c stringproc.c data_types.c simpleCSVsorter.c -o simpleCSVsorter 


test: stringproc.c data_types.c test.c
	rm test.o
	gcc -g -Wall -Werror -fsanitize=address stringproc.c data_types.c test.c -o test.o
	./test.o

clean:
	rm test.o
