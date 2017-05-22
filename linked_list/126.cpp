#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:

        ListNode* mergeKLists(vector<ListNode*>& lists) {
            // empty lists.
            if (lists.size() == 0) {
                return NULL;
            }


            // lists with all linked list empty.
            int unempty_count   = 0;
            for (auto l1 : lists) {
                if (l1) {
                    unempty_count ++;
                }
            }
            if (unempty_count == 0) {
                return NULL;
            }

            ListNode dummy(0);
            ListNode * head = & dummy;

            while(true) {
                int unempty_count   = 0;
                // find smallest 
                int min_val = -1;
                int min_index   = -1;
                int index = -1;
                for (auto l1 :lists) {
                    index ++;
                    if (!l1) {
                        continue;
                    }
                    unempty_count ++;
                    if (min_index == -1) {
                        min_val  = l1->val;
                        min_index = index;
                        continue;
                    }
                    if (l1->val < min_val) {
                        min_val = l1->val;
                        min_index = index;
                        continue;
                    }
                }
                // all list are empty except one.
                if (unempty_count == 1) {
                    break;
                }

                ListNode * min_p    = lists[min_index];

                head->next  = min_p;
                lists[min_index]    = min_p->next;

                head    = head->next;
            }

            // append left
            for (auto l1 : lists) {
                if (l1) {
                    head->next  = l1;
                    break;
                }
            }

            return dummy.next;

        }

        void printList(ListNode * head) {
            ListNode * p = head;
            while (p) {
                cout << p->val << "->" ;
                p   = p->next;
            }
            cout << "NULL" << endl;
        }

};

int main() {
    {
        Solution o;
        cout << "original list:" << endl;

        cout << "merge" << endl;
        vector<ListNode *> lists;
        ListNode * tmp = o.mergeKLists(lists);
        o.printList(tmp);
    }
    {
        ListNode a(1);
        ListNode b(4);
        ListNode c(7);
        ListNode d(10);
        ListNode e(15);

        a.next  = &b;
        b.next  = &c;
        c.next  = &d;
        d.next  = &e;

        ListNode aa(2);
        ListNode bb(3);
        ListNode cc(9);
        ListNode dd(14);
        ListNode ee(20);

        aa.next = &bb;
        bb.next = &cc;
        cc.next = &dd;
        dd.next = & ee;

        Solution o;
        cout << "original list:" << endl;
        o.printList(&a);
        o.printList(&aa);

        cout << "merge" << endl;
        vector<ListNode *> lists;
        lists.push_back(&a);
        lists.push_back(&aa);
        ListNode * tmp = o.mergeKLists(lists);
        o.printList(tmp);
    }

    return 0;
}
