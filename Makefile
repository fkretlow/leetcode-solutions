CXXFLAGS = -std=c++17 -O2 -Wall -Werror -fsanitize=address -fPIC

.PHONY: build clean

build:
	mkdir -p ./build

clean:
	rm -rf ./build

sudoku: build
	$(CXX) $(CXXFLAGS) -o ./build/sudoku ./src/0036_sudoku.cpp
