#include <iostream>
#include <memory>
#include <string>
#include <vector>

std::shared_ptr<std::vector<int>> parse_vector(std::istream& is);
std::shared_ptr<std::vector<std::vector<int>>> parse_matrix(std::istream& is);
bool parse_bool(std::istream& is);

std::ostream& operator<<(std::ostream& os, const std::vector<int>& V);
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& V);
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& V);
