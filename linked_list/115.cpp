#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        // extends from 102
        ListNode *detectCycle(ListNode *head) {
            if (!head) {
                return NULL;
            }

            ListNode * fast = head;
            ListNode * slow = head;
            bool hasCycle   = false;
            while(fast && fast->next) {
                slow    = slow->next;
                fast    = fast->next->next;
                if (slow == fast) {
                    hasCycle    = true;
                    break;
                }
            }

            if (!hasCycle) {
                return NULL;
            }

            // slow pointer moves k steps;
            // fast pointer moves 2*k steps (include k steps and some cycles)
            // so, fast steps minus slow steps: 
            // 2*k -k = some cycles, which means k steps is some cycles.
            // suppose the cycle begins at length m
            // slow point moves: m + x = k 
            // so, if we have a pointer p start from head, p moves 1 steps a time, 
            // and p2 start from where the cycle begins, p2 moves 1 steps a time, too,
            // when p move m+x steps, p2 move k steps, which is some cycles, so p2 remains at where the cycle begins;
            // but we don't know where the cycle begins.

            // if we have a pointer p start from head, p moves 1 steps a time,
            // and p2 start from k,  p2 moves 1 steps a time, too.
            // when p move m steps, p2 move m steps, which is k-x steps, where is p2 now?

            ListNode * p    = head;
            ListNode * p2   = slow;
            while(p !=p2) {
                p   = p->next;
                p2  = p2->next;
            }
            return p2;

        }
};

int main() {

    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    ListNode f(6);
    ListNode g(7);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;
    e.next  = &f;
    f.next  = &g;
    g.next  = NULL;

    Solution o;
    ListNode * head = & a ;
    std::cout << o.detectCycle(head) << endl;

    g.next  = &e;
    std::cout << o.detectCycle(head)->val << endl;

    return 0;
}
