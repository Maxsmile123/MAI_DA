all: main

main: main.o Aho_Corasick.o
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm main.o Aho_Corasick.o -o main

Aho_Corasick.o: Aho_Corasick.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c Aho_Corasick.cpp

main.o: main.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c main.cpp

run:
	./main
clean:
	rm -rf *.o hello