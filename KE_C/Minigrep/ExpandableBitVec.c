#include <stdlib.h>
#include <limits.h>
#include "ExpandableBitVec.h"

const int NO_BITS = sizeof(int) * 8;

int EBV (int size, ExpandableBitVec* out) {
    out->currentSize = size;
    out->backing = malloc(sizeof(int) * size);
    if (out->backing == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < size; i++) {
        out->backing[i] = 0;
    }
    return EXIT_SUCCESS;
}

int ExtendToSize (ExpandableBitVec* self, int size) {
    if (size > self->currentSize) {
        int* newPtr = malloc(sizeof(int) * size);
        if (newPtr == NULL) {
            return EXIT_FAILURE;
        }

        for (int i = 0; i < self->currentSize; i++) {
            newPtr[i] = self->backing[i];
        }
        for (int i = self->currentSize - 1; i < size; i++) {
            newPtr[i] = 0;
        }

        free(self->backing);
        self->backing = newPtr;
    }

    return EXIT_SUCCESS;
}

int Index (ExpandableBitVec* self, int index, bool* out) {
    if (ExtendToSize(self, index + 1) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int backing_ind = index / NO_BITS;
    int internal_ind = index % NO_BITS;

    *out = (self->backing[backing_ind] & (1 << internal_ind)) > 0;
    return EXIT_SUCCESS;
}

int Set (ExpandableBitVec* self, int index) {
    if (ExtendToSize(self, index + 1) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int backing_ind = index / NO_BITS;
    int internal_ind = index % NO_BITS;

    self->backing[backing_ind] |= 1 << internal_ind;

    return EXIT_SUCCESS;
}

int Unset (ExpandableBitVec* self, int index) {
    if (ExtendToSize(self, index + 1) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    int backing_ind = index / NO_BITS;
    int internal_ind = index % NO_BITS;

    self->backing[backing_ind] &= INT_MAX - (1 << internal_ind);

    return EXIT_SUCCESS;
}

void Clear (ExpandableBitVec* self) {
    for (int i = 0; i < self->currentSize; i++) {
        self->backing[i] = 0;
    }
}