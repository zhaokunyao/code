#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

class Solution {
    public:
        bool isAnagram(string s, string t) {
            map<int, int> hash1;
            map<int, int> hash2;

            for (auto c : s) {
                hash1[c] ++;
            }
            for (auto c : t) {
                hash2[c] ++;
            }

            return hash1 == hash2;
        }
};

int main() {
    Solution o;
    {
        cout << o.isAnagram("anagram", "nagaram") << endl;
        cout << o.isAnagram("rat", "car") << endl;
    }

    return 0;
}
