#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        // 103
        ListNode * middleNode(ListNode *head) {
            if (!head) {
                return NULL;
            }
            if (!head->next) {
                return head;
            }
            ListNode * a = head;
            ListNode * b = head;

            while(b->next && b->next->next) {
                a = a->next;
                b = b->next->next;
            }
            return a;

        }

        // 109
        bool isPalindrome(ListNode* head) {
            if (!head) {
                return true;
            }
            ListNode * mid = middleNode(head);
            ListNode * tail = reverseList(mid->next);
            mid->next = NULL;

            while(head && tail) {
                if (head->val != tail->val) {
                    return false;
                }
                head    = head->next;
                tail    = tail->next;

            }
            return true;
        }

        void printList(ListNode * head) {
            while (head) {
                cout << head->val << "->" ;
                head = head->next;
            }
            cout << "NULL" << endl;
        }

        // 108
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

    cout << "go:" << endl;
    cout << o.isPalindrome(&a) <<endl;

    c.val   = 2;
    d.val   = 1;

    cout << "original list:" << endl;
    o.printList(&a);
    cout << "go:" << endl;
    cout << o.isPalindrome(&a) <<endl;


    cout << "original list:" << endl;
    o.printList(&a);
    cout << "go:" << endl;
    cout << o.isPalindrome(&a) <<endl;

    cout << "original list:" << endl;
    o.printList(&a);
    cout << "go:" << endl;
    cout << o.isPalindrome(&a) <<endl;


    return 0;
}
