#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Solution {
    public:
        bool wordPattern(string pattern, string str) {
            stringstream ss(str);
            string token;
            map<char, string> hash;
            map<string, char> hash2;
            int psize = pattern.size();

            int i = 0;
            while(getline(ss, token, ' ')) {
                // pattern 太短
                if (i == psize) {
                    return false;
                }
                char p = pattern[i++];
                if (hash.count(p) == 0) {
                    if (hash2.count(token) != 0) {
                        return false;
                    }
                    hash[p] = token;
                    hash2[token] = p;
                    continue;
                }
                if (hash[p] != token) {
                    return false;
                }
                if (hash2[token] != p) {
                    return false;
                }
            }

            // pattern 太长
            if (i != psize) {
                return false;
            }

            return true;
        }
};

int main() {
    Solution o;
    {
        string pattern = "jquery";
        string str = "jquery";
        cout << o.wordPattern(pattern, str)<<endl;
    }
    {
        string pattern = "abba";
        string str = "dog cat cat dog";
        cout << o.wordPattern(pattern, str)<<endl;
    }
    {
        string pattern = "abba";
        string str = "dog cat cat fish";
        cout << o.wordPattern(pattern, str)<<endl;
    }
    {
        string pattern = "aaaa";
        string str = "dog cat cat dog";
        cout << o.wordPattern(pattern, str)<<endl;
    }
    {
        string pattern = "abba";
        string str = "dog dog dog dog";
        cout << o.wordPattern(pattern, str)<<endl;
    }

    return 0;
}
