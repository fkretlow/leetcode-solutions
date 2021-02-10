/*************************************************************************************************
 *
 * 23. Merge k Sorted Lists (Hard)
 *
 * Given an array of k linked lists that are sorted in ascending order, merge all the linked lists
 * in one sorted linked list and return it.
 *
 * I'm not quite sure why this is considered hard, it's a simple use case for a priority queue.
 * Faster than 91.14%, less memory than 96.24% of C++ solutions.
 *
 ************************************************************************************************/

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>

#include "list.h"

using namespace std;


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) const
    {
        // erase empty lists
        auto it = lists.begin();
        while (it != lists.end()) {
            if (*it == nullptr) it = lists.erase(it);
            else                ++it;
        }

        // create priority queue
        make_heap(lists.begin(), lists.end(), compareLists);
        auto end = lists.end();

        ListNode head { -1 };
        ListNode* cur = &head;
        ListNode* l;

        while (end != lists.begin()) {
            // pop off the next lowest list and detach the first node
            l = lists.at(0);
            lists.at(0) = l->next;
            l->next = nullptr;
            pop_heap(lists.begin(), end, compareLists);

            // if this list is now empty, remove it entirely else reinsert it
            if (*(end - 1) == nullptr)  --end;
            else                        push_heap(lists.begin(), end, compareLists);

            // add the node to the merged list
            cur->next = l;
            cur = cur->next;
        }

        return head.next;
    }
private:
    static bool compareLists(const ListNode* const a, const ListNode* const b)
    {
        return a->val > b->val;
    }
};

int main(void)
{
    ListNode tests[] = {
        ListNode({1,4,5}),
        ListNode({1,3,4}),
        ListNode({2,6})
    };
    vector<ListNode*> lists;
    for (int i = 0; i < 3; ++i) lists.push_back(tests + i);
    // lists.push_back(nullptr);
    // lists.push_back(nullptr);

    ListNode* res = Solution().mergeKLists(lists);
    cout << res << endl;

    return 0;
}
