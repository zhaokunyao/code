#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
#include <stack>
using namespace std;

class Solution {
    public:
        vector<int> findSubstring(string s, vector<string>& words) {
            map<string, int> hash_words;
            for (auto && w : words) {
                hash_words[w]++;
            }

            int len_word = words[0].size();
            int len = s.size();
            int len_words = words.size();
            vector<int> res;
            map<string, int> hash;
            int step = len_words * len_word;
            string token = "";
            for (int i=0; i<step; i+=len_word) {
                string w = "";
                for (int j = i; j<i+len_word; j++) {
                    w += string(1, s[j]);
                }
                hash[w] ++;
                // cout << "push0 " << w << endl;
            }
            // cout << "compare0 " << endl;
            if (hash == hash_words) {
                // cout << "ok: " << 0 << endl;
                res.push_back(0);
            }
            for (int i=step; i<len; i+=len_word) {
                string w = "";
                for (int j = i; j<i+len_word; j++) {
                    w += string(1, s[j]);
                }
                hash[w] ++;
                // cout << "push2 " << w << endl;
                string w2 = "";
                for (int j = i-step; j<i-step+len_word; j++) {
                    w2 += string(1, s[j]);
                }
                hash[w2] --;
                if (hash[w2] == 0) 
                    hash.erase(w2);
                // cout << "pop " << w2 << endl;
                // cout << "===============" << endl;
                for (auto && pair : hash) {
                    // cout << pair.first << ", " << pair.second << endl;
                }
                // cout << "===============" << endl;
                // cout << "compare" << endl;
                if (hash == hash_words) {
                    // cout << "ok: " << i << endl;
                    res.push_back(i-step+len_word);
                }
            }
            return res;
        }
};

int main() {
    Solution o;
    {
        string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
        vector<string> words = {"fooo","barr","wing","ding","wing"};
        vector<int> res = o.findSubstring(s, words);
        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    {
        string s = "wordgoodgoodgoodbestword";
        vector<string> words = {"word","good","best","good"};
        vector<int> res = o.findSubstring(s, words);
        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    {
        string s = "barfoofoobarthefoobarman";
        vector<string> words = {"foo", "bar", "the"};
        vector<int> res = o.findSubstring(s, words);
        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    {
        string s = "barfoothefoobarman";
        vector<string> words = {"foo", "bar"};
        vector<int> res = o.findSubstring(s, words);
        for (auto && n : res) {
            cout << n << ", ";
        }
        cout << endl;
    }
    return 0;
}


