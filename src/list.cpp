#include "list.h"

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
