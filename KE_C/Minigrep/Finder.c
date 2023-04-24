#include <string.h>
#include <stdlib.h>
#include "Finder.h"

int FindMatches (char* text, char* pattern, Matches* out) {
    int text_length = strlen(text);
    int pattern_length = strlen(pattern);

    if (pattern_length == 0) {
        out->count = 0;
        out->matches = NULL;
        return EXIT_SUCCESS;
    }

    Match* maxMatches = malloc(sizeof(Match) * ((text_length / pattern_length) + 1));
    if (maxMatches == NULL) {
        return EXIT_FAILURE;
    }
    int matchesFound = 0;

    for (int i = 0; i < text_length - pattern_length; i++) {
        char current = text[i];

        if (current == pattern[0]) {
            bool works = true;
            for (int offset = 1; offset < pattern_length; offset++) {
                if (text[i + offset] != pattern[offset]) {
                    works = false;
                    break;
                }
            }

            if (works) {
                Match m;
                m.start = i;
                m.end = i + pattern_length - 1;
                maxMatches[matchesFound] = m;
                matchesFound++;
            }
        }
    }

    Match* matches = malloc(sizeof(Match) * matchesFound);
    if (matches == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < matchesFound; i++) {
        matches[i] = maxMatches[i];
    }
    free(maxMatches);



    out->matches = matches;
    out->count = matchesFound;

    return EXIT_SUCCESS;
}

int MatchesToEBV (Matches matches, ExpandableBitVec* ebv, int total_size) {
    if (ExtendToSize(ebv,total_size) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < matches.count; i++) {
        Match m = matches.matches[i];

        for (int ebv_i = m.start; ebv_i <= m.end; ebv_i++) {
            if (Set(ebv, ebv_i) == EXIT_FAILURE) {
                return EXIT_SUCCESS;
            }
        }
    }

    return EXIT_SUCCESS;
}