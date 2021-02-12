/*************************************************************************************************
 *
 * 25. Reverse Nodes in k-Group
 *
 * Given a linked list, revers the nodes k at a time, ignoring a tail of length < k, and return
 * the modified list.
 *
 * Push k nodes on a stack and reverse, abort if there aren't enough nodes left. Could be faster
 * if only int values were swapped, but then pointers to nodes would be invalidated. Faster than
 * 81.32%, less memory than 48.3% of C++ submissions.
 *
 ************************************************************************************************/

#include <exception>
#include <iostream>
#include <stack>
#include "list.h"

/* Log a format string to stdout: log("... %1 ... %2 ... %3 ...", a, b, c, ...) */
template <typename ... Args>
void log(const std::string& fmt, const Args& ... args)
{
    std::cout << "LOG   ";
    std::string::size_type i = 0;
    auto printFmt = [&fmt, &i]()
    {
        while (i < fmt.size()) {
            if (fmt.at(i) == '%') {
                ++i;
                if      (fmt.at(i) == '%')      { ++i; std::cout << '%'; }
                else if (isdigit(fmt.at(i)))    { ++i; break; }
                else throw std::runtime_error("invalid format string");
            }
            else std::cout << fmt.at(i++);
        }
    };
    ((printFmt(), std::cout << args), ..., (std::cout << std::endl));
}

class Solution {
    public:
        ListNode* reverseKGroup(ListNode* n, int k)
        {
            if (k == 0) throw std::runtime_error(std::string(__func__) + ": k must be positive");
            ListNode head { -1, n };
            ListNode *before, *after;
            before = &head;
            std::stack<ListNode*> S;

            bool enough;
            do {
                enough = true;
                for (int i = 0; i < k; ++i) {
                    if (n == nullptr) { enough = false; break; }
                    S.push(n);
                    n = n->next;
                }

                if (enough)
                {
                    after = S.top()->next;
                    before->next = n = S.top(); S.pop();
                    while (!S.empty()) {
                        n->next = S.top(); S.pop();
                        n = n->next;
                    }
                    n->next = after;
                    before = n;
                    n = before->next;
                }

            } while (enough);

            return head.next;
        }
};

int main(int argc, char** argv)
{
    int n = argc > 1 ? std::stoi(argv[1]) : 5;
    int k = argc > 2 ? std::stoi(argv[2]) : 3;

    ListNode *l = new ListNode(1);
    for (int i = 1; i < n; ++i) l->push_back(i+1);
    std::cout << l << std::endl;
    std::cout << Solution().reverseKGroup(l, k) << std::endl;

    delete l;
    return 0;
}
