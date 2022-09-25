CXXFLAGS := -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm
CCX := -std=c++14

all: main

main: main.o suffix_array.o suffix_tree.o
	g++ $(CCX) $(CXXFLAGS) main.o suffix_array.o suffix_tree.o -o main

suffix_array.o: suffix_array.cpp
	g++ $(CCX) $(CXXFLAGS) -c suffix_array.cpp

suffix_tree.o: suffix_tree.cpp
	g++ $(CCX) $(CXXFLAGS) -c suffix_tree.cpp

main.o: main.cpp
	g++ $(CCX) $(CXXFLAGS) -c main.cpp
