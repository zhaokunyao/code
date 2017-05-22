#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// add to end of linked list
class Solution2 {
    private:
        ListNode * head;
        ListNode * tail;
    public:
        Solution2() {
            head    = tail  = NULL;
        }

        void push(int x) {
            ListNode * tmp = new ListNode(x);
            if (!head) {
                head    = tmp;
                tail    = tmp;
                return;
            }
            tail->next = tmp;
            tail    = tail->next;
        }

        void pop() {
            if (!head) {
                return;
            }
            if (!head->next) {
                head    =  tail     = NULL;
                return;
            }
            ListNode * p = head;
            while(true) {
                if (p->next == tail) {
                    break;
                }
                p=p->next;
            }
            p->next = NULL;
            tail    = p;
        }

        int top() {
            if (tail) {
                return tail->val;
            }

            return -1;
        }

        bool empty() {
            if (head) {
                return false;
            }

            return true;
        }

        void printStack() {
            ListNode * p = head;
            while (p) {
                cout << p->val << "->" ;
                p = p->next;
            }
            cout << "NULL" << endl;
        }
};

// add to head of linked list
class Solution {
    private:
        ListNode * dummy;
    public:
        Solution() {
            dummy   = new ListNode(0);
        }

        void push(int x) {
            ListNode * tmp = new ListNode(x);
            tmp->next  = dummy->next;
            dummy->next = tmp;
        }

        void pop() {
            if (!dummy->next) {
                return;
            }
            dummy   = dummy->next;
        }

        int top() {
            if (!dummy->next) {
                return -1;
            }
            return dummy->next->val;
        }

        bool empty() {
            if (dummy->next) {
                return false;
            }

            return true;
        }

        void printStack() {
            ListNode * p = dummy->next;
            while (p) {
                cout << p->val << "->" ;
                p = p->next;
            }
            cout << "NULL" << endl;
        }
};

int main() {
    {
        Solution *o = new Solution();
        o->printStack();
        cout << "empty? " << o->empty() << endl;

        cout << "push 1" << endl;
        o->push(1);
        o->printStack();
        cout << "empty? " << o->empty() << endl;

        cout << "top:" <<  o->top() << endl;

        cout << "pop:" << endl;
        o->pop();
        o->printStack();

        cout << "empty? " << o->empty() << endl;
        o->printStack();

        cout << "push 1" << endl;
        o->push(1);
        o->printStack();
        cout << "push 2" << endl;
        o->push(2);
        o->printStack();
        cout << "push 3" << endl;
        o->push(3);
        o->printStack();

        cout << "pop" << endl;
        o->pop();
        o->printStack();
        cout << "pop" << endl;
        o->pop();
        o->printStack();
        cout << "pop" << endl;
        o->pop();
        o->printStack();
        cout << "pop" << endl;
        o->pop();
        o->printStack();

    }
}
