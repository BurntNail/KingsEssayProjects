#pragma once

#include <stdbool.h>

typedef struct ExpandableBitVec {
    int currentSize;
    int* backing;
} ExpandableBitVec;

int EBV (int size, ExpandableBitVec* out);
int ExtendToSize (ExpandableBitVec* self, int size);
int Index (ExpandableBitVec* self, int index, bool* out);
int Set (ExpandableBitVec* self, int index);
int Unset (ExpandableBitVec* self, int index);
void Clear (ExpandableBitVec* self);