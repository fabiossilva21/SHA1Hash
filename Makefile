include_dirs = -Iinc
CPPFLAGS = $(include_dirs) -std=c++14

all: out/sha1algorithm.o out/test run

out/sha1algorithm.o: src/Sha1Algorithm.cpp inc/Sha1Algorithm.hpp
	mkdir -p out
	g++ $(CPPFLAGS) -c src/Sha1Algorithm.cpp -o out/sha1algorithm.o

out/test: out/sha1algorithm.o tests/Sha1AlgorithmTest.cpp
	g++ $(CPPFLAGS) out/sha1algorithm.o tests/Sha1AlgorithmTest.cpp -o out/test

run: out/test
	./out/test

clean: 
	rm -rf out/