#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode* deleteDuplicates(ListNode* head) {

            ListNode * p = head;
            // 其实也没有必要用2个指针
            while(p) {
                ListNode * p2   =   p;
                while (p2 && p2->val == p->val) {
                    p2 = p2->next;
                }
                p->next  = p2;
                p = p->next;
            }
            return head;
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
    ListNode b(1);
    ListNode c(2);
    a.next  = &b;
    b.next  = &c;
    c.next  = NULL;


    Solution o;
    cout << "original list:" << endl;
    o.printList(&a);
    cout << "delete " << endl;
    ListNode  * ret = o.deleteDuplicates(&a);
    o.printList(ret);

    ListNode aa(1);
    ListNode bb(1);
    ListNode cc(2);
    ListNode dd(2);
    ListNode ee(2);
    aa.next  = &bb;
    bb.next  = &cc;
    cc.next  = &dd;
    dd.next  = &ee;
    ee.next  = NULL;
    cout << "original list:" << endl;
    o.printList(&aa);
    cout << "delete " << endl;
    o.printList(o.deleteDuplicates(&aa));

    return 0;
}
