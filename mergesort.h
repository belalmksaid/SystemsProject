#ifndef MERGESORT_H
#define MERGESORT_H

#include "data_types.h"

int compare(datarow A, datarow B, int index);

datarow * merge(datarow * A, int nA, datarow * B, int nB, int index);

datarow * sort(datarow * data, int ndata, int index);

datarow * mergesort(datarow * data, int index, int nrows );

#endif
