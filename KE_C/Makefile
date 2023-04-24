mandlebrotObject: Mandlebrot/Mandlebrot.c
	mkdir -p Mandlebrot/target
	gcc -Ofast -g -Wall -Wextra -Wpedantic -c Mandlebrot/Mandlebrot.c -o Mandlebrot/target/Mandlebrot.o

mandlebrot: mandlebrotObject
	gcc -Ofast -g Mandlebrot/target/Mandlebrot.o -o Mandlebrot/target/Mandlebrot

minigrepObject: Minigrep/Minigrep.c Minigrep/ExpandableBitVec.c Minigrep/Finder.c
	mkdir -p Minigrep/target
	gcc -Ofast -g -Wall -Wextra -Wpedantic -c Minigrep/Minigrep.c -o Minigrep/target/Minigrep.o
	gcc -Ofast -g -Wall -Wextra -Wpedantic -c Minigrep/ExpandableBitVec.c -o Minigrep/target/ExpandableBitVec.o
	gcc -Ofast -g -Wall -Wextra -Wpedantic -c Minigrep/Finder.c -o Minigrep/target/Finder.o


minigrep: minigrepObject
	gcc -Ofast -g Minigrep/target/Minigrep.o Minigrep/target/ExpandableBitVec.o Minigrep/target/Finder.o -o Minigrep/target/Minigrep


clean:
	rm -rf Minigrep/target/
	rm -rf Mandlebrot/target/