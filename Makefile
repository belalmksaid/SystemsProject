all: simpleCSVsort

simpleCSVsort: mergesort.c stringproc.c datatypes.c
	gcc -g mergesort.c stringproc.c datatypes.c -o simpleCSVsorter 
