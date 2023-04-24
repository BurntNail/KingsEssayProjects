#pragma once

#include "ExpandableBitVec.h"

typedef struct Match {
    int start;
    int end;
} Match;

typedef struct Matches {
    Match* matches;
    int count;
} Matches;

int FindMatches (char* text, char* pattern, Matches* out);
int MatchesToEBV (Matches matches, ExpandableBitVec* ebv, int total_size);