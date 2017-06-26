#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;
struct RandomListNode{
    int label;
    RandomListNode *next;
    RandomListNode(int x) : label(x), next(NULL) {}
    RandomListNode *random;
};

class Solution {
    public:
        RandomListNode *copyRandomList(RandomListNode *head) {
            if (!head) {
                return head;
            }
            map<long, long> hash;
            RandomListNode * p  = head;
            RandomListNode dummy(0);
            RandomListNode * dp = &dummy;
            while(p) {
                RandomListNode *a = new RandomListNode(p->label);
                a->random   = p->random;
                dp->next    = a;
                hash[(long)p] = (long)a;
                dp = dp->next;
                p =  p->next;
            }
            dp = & dummy;
            dp = dp->next;
            while(dp) {
                dp->random = (RandomListNode*)hash[(long)dp->random];
                dp = dp->next;
            }
            return dummy.next;
        }

        void printList(RandomListNode * head) {
            RandomListNode * p  = head;
            while(p) {
                cout << p->label << "->";
                p = p->next;
            }
            cout << endl;
        }
};

int main() {
    Solution o;
    {
        RandomListNode a(1);
        RandomListNode b(2);
        RandomListNode c(3);
        a.next  = &b;
        b.next  = &c;
        a.random    = &c;
        b.random    = &b;
        c.random    = &b;
        o.printList(&a);
    }
    return 0;
}
