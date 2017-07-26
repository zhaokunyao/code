#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
class Solution {
public:
    map<string, string> hash;
    string s_prefix;
    vector <char> chars;

    Solution() {
        hash.clear();
        s_prefix = "http://tinyurl.com/";
        for (int i = 0; i<26; i++) {
            chars.push_back('a' + i);
            chars.push_back('A' + i);
        }
        for (int i =0; i<10; i++) {
            chars.push_back('0' + i);
        }
    }

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        int len = 62;
        string key = "";

        while(true) {
            string url = "";
            for (int i = 0; i<6; i++) {
                int r = rand() % len;
                url += string(1, chars[r]);
            }
            key = s_prefix + url;
            if (hash.count(key) == 0) {
                break;
            }
        }

        hash[key] = longUrl;
        return key;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        if (hash.count(shortUrl) > 0) {
            return hash[shortUrl];
        }
        return "";
    }
};


int main() {
    Solution *o = new Solution();
    {
        string url = "https://leetcode.com/problems/design-tinyurl";
        cout << o->decode(o->encode(url)) << endl;
    }
    {
        string url = "https://leetcode.com/problems/design-tinyurl222";
        cout << o->decode(o->encode(url)) << endl;
    }
    return 0;
}

