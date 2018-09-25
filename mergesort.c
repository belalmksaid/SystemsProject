#include "simpleCSVsorter.h"

int compare(datarow A, datarow B, int index){
	if(A.cells[index].data_type == INT){
		if(A.cells[index].num_datum > B.cells[index].num_datum) {
			return 1;
		}
		else if(A.cells[index].num_datum < B.cells[index].num_datum){
			return -1;
		}
		return 0;
	}	
	return strcmp(A.cells[index].str_datum, B.cells[index].str_datum);
}

datarow * merge(datarow * A, int nA, datarow * B, int nB, int index){
	datarow * merged_data = malloc((nA + nB)*sizeof(datarow));
	int Acount = 0;
	int Bcount = 0;
	int Ccount = 0;
	while(Acount != nA && Bcount != nB){
		int comp = compare(A[nA], B[nB], index);
		if(comp >= 0){
			merged_data[Ccount++] = A[Acount++];	
		}
		else {
			merged_data[Ccount++] = B[Bcount++];
		}
	}
	while(Acount != nA) {
		merged_data[Ccount++] = A[Acount++]
	} 
	while(Bcount != nB) {
		merged_data[Ccount++] = B[Bcount++]
	} 
	return merged_data;
}



datarow * mergesort(datarow * data, int index, int nrows ) {
  //first divide data into 2 arrays of equal length. Sort each of those. Then merge them.	
/*	cell * A = malloc(data.size/2 * sizeof(struct cell));
	cell * B = malloc(data.size/2 * sizeof(struct cell));
	memcpy(A, &data.cells, data.size/2*sizeof(struct cell));
	memcpy(B, &data.cells[data.size/2], data.size/2*sizeof(struct cell)); */
	datarow * sorted_data = malloc(nrows*sizeof(struct datarow));
	int n_null = 0;
	for(int i = 0; i < nrows; ++i){
		if(data[i][index].is_empty == true){
			sorted_data[n_null++] = data[i];
		}
	}
	int n_val = nrows - n_null;
	int nA = n_val/2;
	int nB = n_val/2;
	if(n_val % 2 != 0) nB++;
	datarow * A = malloc(nA * sizeof(datarow));
	datarow * B = malloc(nB * sizeof(datarow));


	merge(A, nA, B, nB);

}
