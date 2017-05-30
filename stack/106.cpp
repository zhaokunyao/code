#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

class Solution {
    public:
        string simplifyPath(string path) {
            string token;
            stringstream ss(path);
            stack<string> sk;
            while(getline(ss, token, '/')) {
                cout << "GET TOKEN: " + token << endl;
                if (token == "." || token == "") {
                    continue;
                }
                if (token == "..") {
                    if (!sk.empty()) {
                        sk.pop();
                    }
                    continue;
                }
                sk.push(token);
            }

            string res = "";
            while(not sk.empty()) {
                if (res == "") {
                    res = sk.top();
                } else {
                    res = sk.top() + "/"+ res;
                }
                sk.pop();
            }
            return "/" + res;
        }
};

int main() {
    Solution * o = new Solution();
    {
        string s = "/..";
        cout << o->simplifyPath(s) << endl;
    }
    {
        string s = "/home/";
        cout << o->simplifyPath(s) << endl;
    }
    {
        string s = "/home/work";
        cout << o->simplifyPath(s) << endl;
    }
    {
        string s = "/a/./b/../../c/";
        cout << o->simplifyPath(s) << endl;
    }
    return 0;
}
