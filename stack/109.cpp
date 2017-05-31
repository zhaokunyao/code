#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <map>

using namespace std;

class Solution {
    public:
        string removeDuplicateLetters(string s) {
            if (s == "") {
                return s;
            }
            stack<int>sk;
            map<char, int>m;
            map<char, int>m2;

            for(auto c : s) {
                if (m.count(c) == 0) {
                    m[c] = 0;
                    m2[c] = 0;
                }
                m[c] ++;
                m2[c] = 1;
            }

            for(auto c : s) {
                if (sk.empty()) {
                    // cout << "push1: " << c << endl;
                    sk.push(c);
                    m[c]--;
                    m2[c] = 0;
                    continue;
                }

                // used
                if (m2[c] == 0) {
                    m[c]--;
                    continue;
                }

                char x = sk.top();
                // pop 
                if ( c < x) {
                    while(c < x) {
                        if (m[x] == 0) {
                            break;
                        }
                        m2[x] = 1;
                        // m[x] ++;
                        // cout << "pop1 " << x << endl;
                        sk.pop();
                        if (sk.empty()) {
                            break;
                        }
                        x = sk.top();
                    }
                    // cout << "push2 " << c << endl;
                    sk.push(c);
                    m[c]--;
                    m2[c] = 0;
                    continue;
                }

                // cout << "push3 " << c << endl;
                sk.push(c);
                m[c]--;
                m2[c] = 0;

            }

            string res = "";
            while(not sk.empty()) {
                res = string(1, sk.top()) +  res;
                sk.pop();
            }
            return res;
        }
};

int main() {
    Solution * o = new Solution();
    {
        string s = "bbcaac";
        cout << o->removeDuplicateLetters(s) << endl;
    }
    {
        string s = "bcabc";
        cout << o->removeDuplicateLetters(s) << endl;
    }
    {
        string s = "cbacdcbc";
        cout << o->removeDuplicateLetters(s) << endl;
    }
    return 0;
}
