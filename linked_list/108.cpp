#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* reverseList(ListNode* head) {
            if (!head) {
                return NULL;
            }
            ListNode * p = head->next;
            ListNode * p2 = head;
            while (p) {
                ListNode * tmp = p->next;
                p->next = p2;
                p2 = p;
                p = tmp;
            }
            head->next = NULL;
            return p2;
        }

        ListNode* reverseList2(ListNode* head) {
            if (!head) {
                return head;
            }
            if (!head->next) {
                return head;
            }

            ListNode * tmp = reverseList2(head->next);
            // guiyi
            head->next->next    = head;
            head->next = NULL;
            return tmp;
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
    cout << "original list:" << endl;
    o.printList(&a);

    cout << "reverse:" << endl;
    // ListNode * tmp = o.reverseList(&a);
    ListNode * tmp = o.reverseList2(&a);
    o.printList(tmp);

    return 0;
}
