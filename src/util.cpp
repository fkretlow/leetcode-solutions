#include <cctype>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

std::shared_ptr<std::vector<int>> parse_vector(std::istream& is)
{
    char c;
    int i;
    auto V = std::make_shared<std::vector<int>>();

    while ((c = is.peek()) != '[') {
        if (isspace(c)) is.get();
        else            goto error;
    }
    is.get();

    while (!is.eof()) {
        c = is.peek();
        if      (isdigit(c))                { is >> i; V->push_back(i); }
        else if (c == ',' || isspace(c))    is.get();
        else if (c == ']')                  { is.get(); break; }
        else                                goto error;
    }

    return V;
error:
    std::stringstream msg;
    msg << __func__ << ": unexpected char '" << (char)is.peek() << "' at position " << is.tellg();
    throw std::runtime_error(std::string(msg.str()));
}

std::shared_ptr<std::vector<std::vector<int>>> parse_matrix(std::istream& is)
{
    char c;
    int i;
    auto V = std::make_shared<std::vector<std::vector<int>>>();

    while ((c = is.peek()) != '[') {
        if (isspace(c)) is.get();
        else goto error;
    }
    is.get();

    while (!is.eof()) {
        c = is.peek();
        if (c == '[') {
            is.get();
            V->push_back(std::vector<int>());
            auto &last = V->back();
            while (!is.eof()) {
                c = is.peek();
                if      (isdigit(c))                { is >> i; last.push_back(i); }
                else if (c == ',' || isspace(c))    is.get();
                else if (c == ']')                  { is.get(); break; }
                else                                goto error;
            }
        }
        else if (c == ',' || isspace(c)) is.get();
        else if (c == ']')               { is.get(); break; }
        else                             goto error;
    }

    return V;
error:
    std::stringstream msg;
    msg << __func__ << ": unexpected char '" << (char)is.peek() << "' at position " << is.tellg();
    throw std::runtime_error(std::string(msg.str()));
}

bool parse_bool(std::istream& is)
{
    std::string s;
    bool r;
    while (isspace(is.peek())) is.get();
    if      (is.peek() == 'f')  { s = "false"; r = false; }
    else if (is.peek() == 't')  { s = "true";  r = true; }
    else                        goto error;

    for (auto it = s.cbegin(); it != s.cend(); ++it) {
        if (*it != is.peek()) goto error;
        is.get();
    }
    return r;
error:
    std::stringstream msg;
    msg << __func__ << ": unexpected char '" << (char)is.peek() << "' at position " << is.tellg();
    throw std::runtime_error(std::string(msg.str()));
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& V)
{
    os << '[';
    if (V.size() > 0) {
        for (auto it = V.cbegin(); it != V.cend() - 1; ++it) os << *it << ',';
        os << V.back();
    }
    return os << ']';
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& V) {
    os << '[';
    if (V.size() > 0) {
        for (auto it = V.cbegin(); it != V.cend() - 1; ++it) os << *it << ',';
        os << V.back();
    }
    return os << ']';
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& V)
{
    os << '[';
    if (V.size() > 0) {
        for (auto it = V.cbegin(); it != V.cend() - 1; ++it) os << '"' << *it << "\",";
        os << '"' << V.back() << '"';
    }
    return os << ']';
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<std::string>>& V) {
    os << '[';
    if (V.size() > 0) {
        for (auto it = V.cbegin(); it != V.cend() - 1; ++it) os << *it << ',';
        os << V.back();
    }
    return os << ']';
}

template<typename T>
void print_matrix(std::ostream& os, std::vector<std::vector<T>> const& M)
{
    for (const std::vector<T>& row : M) {
        for (const T& x : row) os << x << ' ';
        os << std::endl;
    }
}
