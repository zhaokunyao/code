#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode * phead;
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        phead   = head;
        srand (time(NULL));
    }

    /** Returns a random node's value. */
    int getRandom() {
        int a   = phead->val;
        int i   = 1;
        ListNode * node = phead->next;
        while (node) {
            int r   = rand() % (++i) ;
            if (r ==0) {
                a = node->val;
            }
            node    = node->next;
        }

        return a;
    }
};

int main() {
    ListNode * head = new ListNode(0);
    head->next = new ListNode(1);
    head->next->next = new ListNode(2);

    Solution * obj = new Solution(head);
    int param_1 = obj->getRandom();
    cout << param_1 << endl;
}
