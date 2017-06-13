#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool isIsomorphic(string s, string t) {
            map<char, int> hash;
            map<char, int> hash2;
            int length = s.size();
            for (int i=0; i<length; i++){
                char key = s[i];
                char value = t[i];
                if (hash.count(key) == 0) {
                    hash[key] = value;
                    if (hash2.count(value) == 0) {
                        hash2[value] = key;
                    } else {
                        return false;
                    }
                    continue;
                }

                if (value != hash[key]) {
                    return false;
                }
                if (key != hash2[value]) {
                    return false;
                }
            }
            return true;
        }
};

int main() {
    Solution o;
    {
        cout << o.isIsomorphic("egg", "add") << endl;
        cout << o.isIsomorphic("foo", "bar") << endl;
        cout << o.isIsomorphic("paper", "title") << endl;
        cout << o.isIsomorphic("ab", "aa") << endl;
    }

    return 0;
}
