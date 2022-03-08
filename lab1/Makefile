all: main

main: main.o BS.o ShakerSort.o
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm main.o ShakerSort.o BucketSort.o -o main

BS.o: BucketSort.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c BucketSort.cpp

ShakerSort.o: ShakerSort.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c ShakerSort.cpp

main.o: main.cpp
	g++ -std=c++14 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm -c main.cpp

run:
	./main
clean:
	rm -rf *.o hello