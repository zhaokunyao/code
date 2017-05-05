#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        bool hasCycle(ListNode *head) {
            // 空list无环
            if (!head) {
                return false;
            }
            // 只有一个node的list无环
            if (!head->next) {
                return false;
            }
            // 二个指针都指向list的头部
            ListNode * a = head;
            ListNode * b = head;

            // 不需要对a->next进行判断
            // 因为b肯定在a的前面，已经可以保证a->next不为null
            while(b->next && b->next->next) {
                // a指针每次移动一步
                a = a->next;
                // b指针每次移动二步
                b = b->next->next;
                // 如果b与a重合，则有环
                if (a == b ) {
                    return true;
                }
            }

            // 达到list尾部，则无环
            return false;

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
    ListNode * head = & a ;
    std::cout << o.hasCycle(head) << endl;

    g.next  = &e;
    std::cout << o.hasCycle(head) << endl;

    return 0;
}
