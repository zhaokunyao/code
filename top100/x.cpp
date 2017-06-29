#include <iostream>
#include <limits.h>
#include <map>
#include <stack>
#include <vector>
#include <cmath>
using namespace std;


class Solution {
    public:
        bool isPalindrome(string t) {
            string s = "";
            for (auto && c : t) {
                c = tolower(c);
                if (c >= 'a' && c <= 'z') {
                    s += string(1, c);
                } else if (c >='0' && c <='9') {
                    s += string(1, c);
                }
            }
            int len = s.size();
            if (len == 0) return true;
            if (len % 2 ==1) {
                int mid = len /2;
                for (int i=1; i<=mid ; i++) {
                    if (s[mid-i] != s[mid+i]) {
                        return false;
                    }
                }

                return true;
            }
            int mid = len /2;
            int left = mid -1;
            int right = mid;
            // cout << left << ":" << right << endl;

            while(left >=0 ) {
                if (s[left--] != s[right++]) {
                    return false;
                }
            }
            return true;

        }
};

int main() {
    Solution o;
    {
        string s ="0P";
        cout  << o.isPalindrome(s) << endl;
    }
    {
        string s ="A man, a plan, a canal: Panama";
        cout  << o.isPalindrome(s) << endl;
    }
    {
        string s ="race a car";
        cout  << o.isPalindrome(s) << endl;
    }
    return 0;
}
