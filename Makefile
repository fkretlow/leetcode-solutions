CXXFLAGS = -std=c++17 -O2 -Wall -Werror -fsanitize=address -fPIC

.PHONY: build clean

build:
	mkdir -p ./build

clean:
	rm -rf ./build

sudoku: build
	$(CXX) -o ./build/sudoku ./src/0037_sudoku.cpp

subsets: build
	$(CXX) -o ./build/subsets ./src/0078_subsets.cpp ./src/util.cpp

subsets2: build
	$(CXX) -o ./build/subsets2 ./src/0090_subsets.cpp ./src/util.cpp

min_window_substring: build
	$(CXX) -o ./build/substr ./src/0076_minimum_window_substring.cpp

