/*************************************************************************************************
 *
 * 24. Swap Nodes in Pairs
 *
 * Given a linked list, swap every two adjacent nodes and return its head.
 *
 ************************************************************************************************/

#include <iostream>
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
        ListNode* swapPairs(ListNode* l)
        {
            ListNode head { -1, l };
            ListNode *prev, *cur;
            for (prev = &head, cur = l; cur && cur->next; prev = prev->next->next, cur = prev->next) {
                // log("prev=%0, cur=%1, next=%2", prev->val, cur->val, cur->next->val);
                prev->next = cur->next;
                cur->next = prev->next->next;
                prev->next->next = cur;
            }
            return head.next;
        }
};

int main(void)
{
    // ListNode l1({ 1,2,3,4 });
    // ListNode l1({ 1,2,3 });
    // ListNode l1({ 1,2 });
    ListNode l1({ 1 });
    std::cout << Solution().swapPairs(&l1) << std::endl;

    std::cout << Solution().swapPairs(nullptr) << std::endl;
    return 0;
}
