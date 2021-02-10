/*************************************************************************************************
 *
 * 19. Remove Nth Node From End of List
 *
 * Given the head of a linked list, remove the nth node from the end of the list and return its
 * head.
 *
 * Faster than 84.04%, less memory than 95.94% of C++ submissions.
 *
 ************************************************************************************************/

#include <iostream>
#include "list.h"

using namespace std;

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, const unsigned short n)
    {
        const unsigned short i = ListSize(head) - n;
        return removeNode(head, i);
    }

private:
    unsigned short ListSize(const ListNode* n)
    {
        unsigned short size = 0;
        while (n) { n = n->next; ++size; }
        return size;
    }
    ListNode* removeNode(ListNode* head, const unsigned short i)
    {
        if (i == 0) return head->next;
        ListNode* n = head;
        unsigned short j = 0;
        while (j < i-1) {
            n = n->next; ++j;
        }
        n->next = n->next->next;
        return head;
    }
};


int main(void)
{
    Solution instance;

    ListNode l1 { {1,2,3,4,5} };
    cout << instance.removeNthFromEnd(&l1, 2) << endl;

    ListNode l2 { {1} };
    cout << instance.removeNthFromEnd(&l2, 1) << endl;

    ListNode l3 { {1,2} };
    cout << instance.removeNthFromEnd(&l3, 1) << endl;

    ListNode l4 { {1,2} };
    cout << instance.removeNthFromEnd(&l4, 2) << endl;

    return 0;
}
