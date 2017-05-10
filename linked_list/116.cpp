#include <iostream>
#include <map>
using namespace std;


struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
class Solution {
    public:
        RandomListNode *copyRandomList(RandomListNode *head) {
            RandomListNode dummy(0);
            RandomListNode * dp = &dummy;

            std::map<long, long>  map;

            while (head) {
                // make a new node.
                RandomListNode *x   = new RandomListNode(head->label);
                x->random           = head->random;

                // append to new list
                dp->next    = x;

                // make a map
                map.insert( std::map<long, long>::value_type((long)head, (long)x));

                // next
                dp  = dp->next;
                head    = head->next;
            }

            dp  = &dummy;
            while(dp) {
                if (!dp->random) {
                    dp  = dp->next;
                    continue;
                }
                std::map<long, long>::iterator it;
                it = map.find((long)dp->random);
                dp->random = (RandomListNode *) it->second;
                dp  = dp->next;
            }

            return dummy.next;
        }

        void printList(RandomListNode * head) {
            while (head) {
                cout << head->label << "[random: ";
                if (head->random) {
                    cout << head->random->label;
                } else {
                    cout << "NULL";
                }

                cout << ":" << (long) head << "]" << "->" ;

                head = head->next;
            }
            cout << "NULL" << endl;
        }
};



int main() {
    RandomListNode a(1);
    RandomListNode b(2);
    RandomListNode c(3);
    RandomListNode d(4);
    RandomListNode e(5);
    RandomListNode f(6);
    RandomListNode g(7);

    a.next  = &b;
    b.next  = &c;
    c.next  = &d;
    d.next  = &e;
    e.next  = &f;
    f.next  = &g;
    g.next  = NULL;

    b.random    = &a;
    c.random    = &e;

    Solution    o;
    cout << "original list:" << endl;
    o.printList(&a);

    RandomListNode * tmp = o.copyRandomList(&a);
    cout << "copied list:" << endl;
    o.printList(tmp);
}
