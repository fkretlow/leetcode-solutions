#include "list.h"

void ListNode::push_back(int x)
{
    ListNode* cur = this;
    while (cur->next) cur = cur->next;
    cur->next = new ListNode(x);
}

std::ostream& operator<<(std::ostream& os, const ListNode* L)
{
    os << '[';
    if (!L) return os << ']';

    while (L->next) {
        os << L->val << ',';
        L = L->next;
    }
    return os << L->val << ']';
}
