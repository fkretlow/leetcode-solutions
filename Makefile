CXXFLAGS = -std=c++17 -O2 -Wall -Werror -fsanitize=address -fPIC

.PHONY: build clean

build:
	mkdir -p ./build

clean:
	rm -rf ./build

sudoku: build
	$(CXX) $(CXXFLAGS) -o ./build/sudoku ./src/0037_sudoku.cpp

subsets: build
	$(CXX) $(CXXFLAGS) -o ./build/subsets ./src/0078_subsets.cpp ./src/util.cpp

subsets2: build
	$(CXX) $(CXXFLAGS) -o ./build/subsets2 ./src/0090_subsets.cpp ./src/util.cpp

window: build
	$(CXX) $(CXXFLAGS) -o ./build/substr ./src/0076_minimum_window_substring.cpp

validate-bst: build
	$(CXX) $(CXXFLAGS) -o ./build/validate-bst ./src/0078_validate_bst.cpp ./src/tree.cpp

mode-bst: build
	$(CXX) $(CXXFLAGS) -o ./build/mode-bst ./src/0501_bst_mode.cpp ./src/tree.cpp ./src/util.cpp

sort-colors: build
	$(CXX) $(CXXFLAGS) -o ./build/sort-colors ./src/0075_sort_colors.cpp ./src/util.cpp
