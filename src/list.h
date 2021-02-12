#pragma once

#include <iostream>
#include <initializer_list>

struct ListNode {
    int val;
    ListNode *next;
    ListNode()                      : val(0), next(nullptr) {}
    ListNode(int x)                 : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next)    {}
    ListNode(std::initializer_list<int> init) {
        auto it = init.begin();
        val = *it++;
        next = nullptr;

        ListNode* cur = this;
        while (it != init.end()) {
            cur->next = new ListNode(*it++);
            cur = cur->next;
        }
    }
    void push_back(int x);
};

std::ostream& operator<<(std::ostream&, const ListNode*);
