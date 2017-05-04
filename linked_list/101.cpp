#include <iostream>
#include <limits.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

int main() {
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);


    a.next = &b;
    b.next = &c;
    //a-->b-->c->null
    cout << a.val << endl;
    cout << a.next->val << endl;
    cout << a.next->next->val << endl;
    cout << "-------------" << endl;

    ListNode * head = &a;
    // head(a)-->b-->c-->null
    while( head) {
        cout << head->val << endl;
        head    = head->next;
    }
    cout << "-------------" << endl;

    ListNode dummy(INT_MIN);
    dummy.next  = &a;
    ListNode * head1 = & dummy;
    // head1(dummy)-->a-->b-->c-->null
    while(head1->next) {
        cout << head1->next->val << endl;
        head1 = head1->next;
    }
    return 0;
}
