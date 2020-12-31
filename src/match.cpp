/*************************************************************************************************
 *
 * match.cpp
 *
 * A minimal regex engine that supports the special characters `*` and `.`. Batteries and tests
 * included.
 *
 * Author: Florian Kretlow. For good measure, license would be MIT.
 *
 ************************************************************************************************/

#include <string>
#include <iostream>
#include <forward_list>

class Regex {
    friend std::ostream& operator<<(std::ostream&, const Regex&);
public:
    Regex(std::string& p) : pattern(p) {};
    bool match(const std::string &s);
private:
    bool match_(std::string::size_type pi, std::string::size_type si);
    std::string pattern;
    std::string string;
};

std::ostream& operator<<(std::ostream& os, const Regex& re)
{
    return os << "Regex('" << re.pattern << "')";
}

/* Boilerplate for the recursive matching algorithm. */
bool Regex::match(const std::string &s)
{
    string = s;
    return match_(0, 0);
}

/* Perform the match recursively. */
bool Regex::match_(std::string::size_type pi,   /* current index in the pattern string */
                   std::string::size_type si)   /* current index in the string */
{
    /* Exit conditions */
    if (pi >= pattern.size() && si >= string.size()) {
        return true;
    } else if ((  pi >= pattern.size()  && !(si >= string.size())) ||
               (!(pi >= pattern.size()) &&   si >= string.size() )) {
        return false;
    }

    bool any = pattern[pi] == '.';
    bool many = pattern[pi+1] == '*';

    if (!any) {
        if (!many) {
            if (string[si] != pattern[pi])
                return false;
            else
                return match_(pi + 1, si + 1);
        } else {
            /* We can have any number of the current pattern char, including 0. */
            if (string[si] != pattern[pi])
                /* Chars don't match, advance the pattern. */
                return match_(pi + 2, si);
            else
                /* Chars match. Now, we can't do maximal munch, so advance both indices or either
                 * of the two and try to match the rest of the string. OR will abort if something
                 * succeeds. */
                return match_(pi + 2, si) || match_(pi, si + 1) || match_(pi + 2, si + 1);
        }
    } else {
        /* We can have any character so we don't need to compare. */
        if (!many)
            /* Any single char, simplest case: nothing to do. */
            return match_(pi + 1, si + 1);
        else
            /* We can have 0 or more arbitrary chars. No maximal munch: same as above. */
            return match_(pi + 2, si) || match_(pi, si + 1) || match_(pi + 2, si + 1);
    }
}

class TestCase {
public:
    TestCase(std::string p, std::string s, bool exp) : re(p), string(s), expected(exp) {};
    bool run();
private:
    Regex re;
    std::string string;
    bool expected;
};

bool TestCase::run()
{
    bool success = re.match(string) == expected;
    if (success) {
        std::cout << "OK:   " << re
                  << (expected ? " matches " : " doesn't match ")
                  << '\'' << string << '\'' << '.' << std::endl;
    } else {
        std::cout << "FAIL: " << re
                  << (expected ? " doesn't match " : " matches ")
                  << '\'' << string << '\'' << '.' << std::endl;
    }
    return success;
}

int main(int argc, char *argv[])
{
    int rc = 0;

    if (argc == 3) {
        std::string p { argv[1] };
        const std::string s { argv[2] };
        Regex re { p };

        std::cout << std::boolalpha << re.match(s) << std::endl;
    }

    else {
        std::forward_list<TestCase> tests {
            TestCase("abc", "abc", true),
            TestCase(".*c", "abc", true),
            TestCase("a*a", "aaaaaaa", true),
            TestCase("a*a", "a", true),
            TestCase("hi*.a", "hiiiiiya", true),
            TestCase("hi*a", "hiiiiiya", false)
        };

        for (auto &test : tests) rc = test.run() ? rc : -1;
    }

    return rc;
}
