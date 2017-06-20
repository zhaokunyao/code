#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        string fractionToDecimal(int numerator, int denominator) {
            if (numerator == 0) {
                return "0";
            }
            long num    = (long) numerator;
            long den    = (long) denominator;
            int minus   = 0;
            if (numerator <0) {
                num *= -1;
                minus ++;
            }
            if (denominator <0) {
                den *= -1;
                minus ++;
            }
            string s;

            // 负数
            if (minus % 2 == 1) {
                s += "-";
            }
            long left =  num / den;
            long right = num % den;
            s += to_string(left);

            if (right == 0) {
                return s;
            }
            s += ".";
            string s2 = "";
            map<long, int> hash;
            int i = 1;
            hash[right] = i;
            while(true) {
                num = right * 10;
                left = num / den;
                right = num % den;
                s2 += to_string(left);
                if (right == 0) {
                    s += s2;
                    break;
                }
                if (hash[right] >0) {
                    // s += "(" + s2 + ")";
                    // 需要插入到s2里面一个合适的位置
                    s2.insert(hash[right]-1, "(");
                    s += s2 + ")";
                    break;
                }
                i++;
                hash[right] = i;
            }

            return s;
        }
};

int main() {
    Solution o;
    {
        int numerator = 0;
        int denominator = -5;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }
    {
        int numerator = 1;
        int denominator = 6;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }
    {
        int numerator = 2147483648;
        int denominator = 1;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }

    {
        int numerator = 2147483648;
        int denominator = -1;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }
    {
        int numerator = 1;
        int denominator = 2;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }
    {
        int numerator = 2;
        int denominator = 1;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }
    {
        int numerator = 2;
        int denominator = 3;
        cout << o.fractionToDecimal(numerator, denominator) << endl;
    }
    return 0;
}
