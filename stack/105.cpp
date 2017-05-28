#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Solution {
    public:
        string decodeString(string s) {
            stack <string> sk;
            string str = "";

            int len = s.length();
            for (int i=0 ; i<len; i++) {
                if (s[i] != ']') {
                    char c = s[i];
                    string tmp = string(1, c);
                    cout << "\tpushing " << tmp << endl;
                    sk.push(tmp);
                    continue;
                }
                string str_bracket;
                int factor  = 1;
                int repeat  = 0;
                while(true) {
                    string sb = sk.top();
                    char c = sk.top()[0];
                    cout << "\tpop1 " << sk.top() << endl;
                    sk.pop();
                    if (isdigit(c)) {
                        repeat = factor * (c - '0') + repeat;
                        factor *= 10;
                        if (sk.empty() || (!sk.empty() &&  !isdigit(sk.top()[0]))) {
                            string tmp = "";
                            for (int j=0; j<repeat; j++) {
                                tmp += str_bracket;
                            }
                            // push back主要是为了解决嵌套的问题
                            // 貌似用递归也是可以解决的
                            cout << "\tpushing2: " << tmp << endl;
                            sk.push(tmp);
                            break;
                        }
                        continue;
                    }

                    if (c == '[') {
                        continue;
                    }

                    str_bracket = sb + str_bracket;
                }
            }

            while(not sk.empty()) {
                str = sk.top() + str;
                cout << "\tpop " << sk.top() << endl;
                sk.pop();
            }

            return str;
        }
};

int main() {
    Solution * o = new Solution();
    {
        string s = "3[a]2[bc]";
        cout << o->decodeString(s) << endl;
    }
    {
        string s = "3[a2[c]]";
        cout << o->decodeString(s) << endl;
    }
    {
        string s = "2[abc]3[cd]ef";
        cout << o->decodeString(s) << endl;
    }
    return 0;
    {
        string s = "fc";
        cout << o->decodeString(s) << endl;
    }
    {
        string s = "f2[e]";
        cout << o->decodeString(s) << endl;
    }
    {
        string s = "f2[e]g";
        cout << o->decodeString(s) << endl;
    }
    {
        string s = "sd2[f2[e]g]i";
        cout << o->decodeString(s) << endl;
    }
    return 0;
}
