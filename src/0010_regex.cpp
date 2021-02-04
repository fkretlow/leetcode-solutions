/*************************************************************************************************
 *
 * 10. Regular Expression Matching
 *
 * A minimal regex engine that supports the special characters `*` and `.`.
 *
 ************************************************************************************************/

#include <string>
#include <iostream>
#include <forward_list>

class Regex {
    friend std::ostream& operator<<(std::ostream&, const Regex&);
public:
    Regex(const std::string& p) : pattern(p) {};
    bool match(const std::string &s) { str = s; return match_(0, 0); }
private:
    bool match_(const std::string::size_type pi, const std::string::size_type si) const;
    std::string pattern;
    std::string str;
};

std::ostream& operator<<(std::ostream& os, const Regex& re)
{
    return os << "Regex('" << re.pattern << "')";
}

/* Perform the match recursively. */
bool Regex::match_(const std::string::size_type pi,   /* current index in the pattern string */
                   const std::string::size_type si)   /* current index in the string */
const {
    bool any  = pattern.size() >= pi+1 && pattern.at(pi)   == '.';
    bool many = pattern.size() >= pi+2 && pattern.at(pi+1) == '*';

    /* Exit conditions */
    if (pi >= pattern.size() && si >= str.size()) {
        return true;
    } else if (pi >= pattern.size() && !(si >= str.size())) {
        return false;
    } else if (!(pi >= pattern.size()) && si >= str.size()) {
        if (!many) return false;
        else       return match_(pi+2, si);
    }

    if (!any) {
        if (!many) {
            if (str.at(si) != pattern.at(pi)) return false;
            else                              return match_(pi+1, si+1);
        } else {
            /* We can have any number of the current pattern char, including 0. */
            if (str.at(si) != pattern.at(pi)) {
                /* Chars don't match, advance the pattern. */
                return match_(pi+2, si);
            } else {
                /* Chars match. Now, we can't do maximal munch, so advance both indices or either
                 * of the two and try to match the rest of the string. OR will abort if something
                 * succeeds. */
                return match_(pi+2, si) || match_(pi, si+1) || match_(pi+2, si+1);
            }
        }
    } else /* any == true */ {
        /* We can have any character so we don't need to compare. */
        if (!many) {
            /* Any single char, simplest case: nothing to do. */
            return match_(pi+1, si+1);
        } else {
            /* We can have 0 or more arbitrary chars. No maximal munch: same as above. */
            return match_(pi+2, si) || match_(pi, si+1) || match_(pi+2, si+1);
        }
    }
}

class TestCase {
public:
    TestCase(std::string p, std::string s, bool exp) : re(p), str(s), expected(exp) {};
    bool run();
private:
    Regex re;
    std::string str;
    bool expected;
};

bool TestCase::run()
{
    bool success = re.match(str) == expected;
    if (success) {
        std::cout << "OK:   " << re
                  << (expected ? " matches " : " doesn't match ")
                  << '\'' << str << '\'' << '.' << std::endl;
    } else {
        std::cout << "FAIL: " << re
                  << (expected ? " doesn't match " : " matches ")
                  << '\'' << str << '\'' << '.' << std::endl;
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
            TestCase("a",           "aa",           false),
            TestCase("a*",          "aa",           true),
            TestCase(".*",          "ab",           true),
            TestCase("c*a",         "a",            true),
            TestCase("ab*",         "a",            true),
            TestCase(".*a",         "a",            true),
            TestCase("c*a*b",       "aab",          true),
            TestCase("mis*is*p*.",  "mississippi",  false),
            TestCase("abc",         "abc",          true),
            TestCase(".*c",         "abc",          true),
            TestCase("a*a",         "aaaaaaa",      true),
            TestCase("a*a",         "a",            true),
            TestCase("hi*.a",       "hiiiiiya",     true),
            TestCase("hi*a",        "hiiiiiya",     false)
        };

        for (auto &test : tests) rc = test.run() ? rc : -1;
    }

    return rc;
}
