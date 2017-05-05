#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        void deleteNode(ListNode* node) {
            node->val   = node->next->val;
            delete node->next;
            node->next  = node->next->next;
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

    // except the tail.
    // o.deleteNode(&g);
    // o.printList();

    cout << "delete f:" << f.val<< endl;
    o.deleteNode(&f);
    o.printList(&a);

    cout << "delete a:" << a.val<< endl;
    o.deleteNode(&a);
    o.printList(&a);

    return 0;
}
