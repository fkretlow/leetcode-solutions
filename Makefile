CXXFLAGS = -std=c++17 -O2 -Wall -Werror -fPIC #-fsanitize=address

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

flatten-tree: build
	$(CXX) $(CXXFLAGS) -o ./build/flatten-tree ./src/0114_flatten_tree.cpp ./src/tree.cpp

traverse-tree: build
	$(CXX) $(CXXFLAGS) -o ./build/traverse-tree ./src/0094_tree_traversal.cpp ./src/tree.cpp ./src/util.cpp

jump-game: build
	$(CXX) $(CXXFLAGS) -o ./build/jump-game ./src/0055_jump_game.cpp ./src/util.cpp

copy-list-with-randptr: build
	$(CXX) $(CXXFLAGS) -o ./build/copy-list-with-randptr ./src/0138_copy_list_with_randptr.cpp ./src/util.cpp

max-subarray: build
	$(CXX) $(CXXFLAGS) -o ./build/max-subarray ./src/0053_max_subarray.cpp ./src/util.cpp

merge-lists: build
	$(CXX) $(CXXFLAGS) -o ./build/merge-lists ./src/0021_merge_lists.cpp ./src/list.cpp

words: build
	$(CXX) $(CXXFLAGS) -o ./build/words ./src/0211_words.cpp
