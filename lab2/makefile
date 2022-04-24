all: main

main: main.o RBT_node.o RBT.o
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm main.o RBT.o RBT_node.o -o main

RBT_node.o: RBT_node.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c RBT_node.cpp

RBT.o: RBT.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c RBT.cpp

main.o: main.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c main.cpp

run:
	./main
clean:
	rm -rf *.o hello