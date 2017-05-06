#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
            ListNode * p1   = headA;
            ListNode * p2   = headB;
            if (!p1 || !p2) {
                return NULL;
            }
            bool isRewind1   = false;
            bool isRewind2   = false;
            while (true) {
                if (p1 == p2) {
                    return p1;
                }
                if (p1->next) {
                    p1 = p1->next;
                } else {
                    if (isRewind1) {
                        return NULL;
                    }
                    p1  = headB;
                    isRewind1 = true;
                }
                if (p2->next) {
                    p2 = p2->next;
                } else {
                    if (isRewind2) {
                        return NULL;
                    }
                    p2  = headA;
                    isRewind2 = true;
                }
            }
        }

        void printList(ListNode * head) {
            while (head) {
                cout << head->val << "->" ;
                head = head->next;
            }
            cout << "NULL" << endl;
        }

};

int main() {
    ListNode a1(1);
    ListNode a2(2);

    ListNode c1(3);
    ListNode c2(4);
    ListNode c3(5);

    ListNode b1(6);
    ListNode b2(7);
    ListNode b3(8);


    a1.next = &a2;
    a2.next = &c1;

    c1.next = &c2;
    c2.next = &c3;

    b1.next = &b2;
    b2.next = &b3;
    b3.next = &c1;



    Solution o;
    cout << "original list:" << endl;
    o.printList(&a1);
    cout << "original list:" << endl;
    o.printList(&b1);

    ListNode * tmp = o.getIntersectionNode(&a1, &b1);
    if (tmp) {
        cout << tmp->val << endl;
    } else {
        cout <<"NULL" << endl;
    }

    ListNode a100(1);
    ListNode b100(1);
    tmp = o.getIntersectionNode(&a100, &b100);
    if (tmp) {
        cout << tmp->val << endl;
    } else {
        cout <<"NULL" << endl;
    }

    return 0;
}
