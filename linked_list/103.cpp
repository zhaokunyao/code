#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    public:
        ListNode * middleNode(ListNode *head) {
            // 空list
            if (!head) {
                return NULL;
            }
            // 只有一个node
            if (!head->next) {
                return head;
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
            }

            // b达到list尾部,a?
            return a;

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
    // 长度7
    std::cout << o.middleNode(head)->val << endl;

    // 长度6
    f.next  = NULL;
    std::cout << o.middleNode(head)->val << endl;

    // 长度3
    c.next  = NULL;
    std::cout << o.middleNode(head)->val << endl;

    // 长度2
    b.next  = NULL;
    std::cout << o.middleNode(head)->val << endl;

    // 长度1
    a.next  = NULL;
    std::cout << o.middleNode(head)->val << endl;


    return 0;
}
