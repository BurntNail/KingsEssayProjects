#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ExpandableBitVec.h"
#include "Finder.h"

const size_t MAX_LINE_SIZE = 512;

int main (int argc, char** argv) {
    switch (argc) {
        case 1:
            fprintf(stderr, "You need to pass in a file as the first argument.\n");
            return -1;
        case 2:
            fprintf(stderr, "You need to pass in a pattern to look for as the second argument.\n");
            return -1;
    }


    FILE *fptr = fopen( argv[1], "r");
    if (fptr == NULL) {
        fprintf(stderr, "Error reading file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    char* pattern = argv[2];
    ExpandableBitVec ebv;
    if (EBV(50, &ebv) == EXIT_FAILURE) {
        fprintf(stderr, "Error creating ExpandableBitVec.\n");
        return EXIT_FAILURE;
    }

    char* line = malloc(sizeof(char) * MAX_LINE_SIZE);
    if (line == NULL) {
        fprintf(stderr, "Error allocating space for line.\n");
        return EXIT_FAILURE;
    }
    ssize_t read;

    while ((read = getline(&line, &MAX_LINE_SIZE, fptr)) != -1) {
        Matches m;
        if (FindMatches(line, pattern, &m) == EXIT_FAILURE) {
            fprintf(stderr, "Error allocating for matches.\n");
            return EXIT_FAILURE;
        }

        if (MatchesToEBV(m, &ebv, read) == EXIT_FAILURE) {
            fprintf(stderr, "Error creating ebv from matches.\n");
            return EXIT_FAILURE;
        }

        for (ssize_t i = 0; i < read; i++) {
            bool isHere = false;
            if (Index(&ebv, i, &isHere) == EXIT_FAILURE) {
                fprintf(stderr, "Error indexing ebv.\n");
                return EXIT_FAILURE;
            }

            if (isHere) {
                printf("\x1B[32m%c\x1B[97m", line[i]);
            } else {
                printf("%c", line[i]);
            }
        }

        Clear(&ebv);
        free(m.matches);
    }
    printf("\n");

    fclose(fptr);
    if (line)
        free(line);

    free(ebv.backing);

    return EXIT_SUCCESS;
}
