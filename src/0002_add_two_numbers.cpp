/*************************************************************************************************
 *
 * 2. Add Two Numbers
 *
 * Given two linked lists of digits representing integers in reverse order, return the sum of the
 * two integers as a linked list of digits in reverse order.
 *
 * Faster than 90.87%, less memory than 74.85% of C++ submissions.
 * (Who cares that the given definition of a linked list makes it really difficult to avoid
 * memory leaks in the limited context of the problem?)
 *
 ************************************************************************************************/

#include <initializer_list>
#include <iostream>

using namespace std;

/* Please! Give us a list header that handles *all* allocations, or use an STL list, or at least
 * smart pointers! */
struct ListNode {
    int val;
    ListNode* next;
    ListNode()                      : val(0), next(nullptr) {}
    ListNode(int x)                 : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next)    {}

    // my additions for testing
    friend ostream& operator<<(ostream&, ListNode);

    ListNode(initializer_list<int> init) {
        auto it = init.begin();
        val = *it++;
        next = nullptr;

        ListNode* cur = this;
        while (it != init.end()) {
            cur->next = new ListNode(*it++);
            cur = cur->next;
        }
    }
};

ostream& operator<<(ostream& os, ListNode L)
{
    os << '[';
    while (L.next) {
        os << L.val << ',';
        L = *L.next;
    }
    return os << L.val << ']';
}

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        int sum = 0;
        int carry = 0;
        ListNode* res = nullptr;
        ListNode* cur = nullptr;

        while (l1 || l2) {
            sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            if (!res) {
                res = cur = new ListNode(sum % 10);
            } else {
                cur->next = new ListNode(sum % 10);
                cur = cur->next;
            }
            carry = sum / 10;
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
        }

        if (carry) cur->next = new ListNode(carry);

        return res;
    }
};

int main(void)
{
    // ListNode l1 = ListNode({2,4,3});
    // ListNode l2 = ListNode({5,6,4});

    // ListNode l1 = ListNode({0});
    // ListNode l2 = ListNode({0});

    ListNode l1 = ListNode({9,9,9,9,9,9,9});
    ListNode l2 = ListNode({9,9,9,9});

    ListNode* res = Solution().addTwoNumbers(&l1, &l2);
    cout << *res << endl;

    // Yes, we are loosing everything except the first nodes of the initial list.
    return 0;
}
