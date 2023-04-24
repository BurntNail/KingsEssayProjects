#include "ExpandableBitVec.h"
#include <fstream>
#include <string>
#include <regex>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	switch (argc) {
	case 1:
		fprintf(stderr, "You need to pass in a file as the first argument.");
		return -1;
	case 2:
		fprintf(stderr, "You need to pass in a pattern to look for as the second argument.");
		return -1;
	}

	std::regex pat(argv[2]);
	ExpandableBitVec bv(256);

	std::ifstream file("jabberwocky.txt");
	std::string line;
	while (std::getline(file, line)) {
		auto match = std::smatch{};
		if (std::regex_search(line, match, pat)) {
			auto prefix = match.prefix();

			for (auto it = match.begin(); it != match.end(); ++it) {
				int start = (*it).length();
				int end = start + (*it).str().length();
				printf("Going from %d to %d\n", start, end);
				for (int i = start; i < end; i++) {
					bv.Set(i);
				}
			}
		}

		for (int col = 0; col < line.length(); col++) {
			if (bv.Index(col)) {
				printf("\x1B[32;1m%c\x1B[37m", line.at(col));
			}
			else {
				printf("%c", line.at(col));
			}
		}
		printf("\n");
		bv.Clear();
	}
}
