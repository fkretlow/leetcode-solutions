/*************************************************************************************************
 *
 * 21. Merge Two Sorted Lists
 * Runtime: 81.85%, memory usage: 97.66%.
 *
 ************************************************************************************************/

#include <iostream>
#include "list.h"

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) const
    {
        if (!l1) return l2;
        if (!l2) return l1;

        ListNode head(-1);
        ListNode *cur = &head;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                cur->next = l1;
                l1 = l1->next;
                cur = cur->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
                cur = cur->next;
            }
        }
        while (l1) {
            cur->next = l1;
            l1 = l1->next;
            cur = cur->next;
        }
        while (l2) {
            cur->next = l2;
            l2 = l2->next;
            cur = cur->next;
        }

        cur->next = nullptr;
        return head.next;
    }
};

void test(ListNode *l1, ListNode *l2)
{
    static const Solution instance;
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    ListNode *res = instance.mergeTwoLists(l1, l2);
    std::cout << res << std::endl;
}

int main()
{
    ListNode l1({1,2,4});
    ListNode l2({1,1,2,3,4,4});
    test(&l1, &l2);
    ListNode l3({0});
    test(nullptr, &l3);
    test(nullptr, nullptr);
    return 0;
}
