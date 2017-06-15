#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
    vector<bool> hash;
    public:
        // The Sieve of Eratosthenes
        int countPrimes(int n) {
            hash.resize(n);
            int count = 0;
            makeHash(n);
            for (int i=2; i<n; i++) {
                if (hash[i] == 1) {
                    count ++;
                }
            }
            return count;
        }

        void makeHash(int n) {
            int sq = (int)sqrt(n) + 1;
            // cout << "sq: " << sq << endl;
            // default.
            for (int i = 2; i<n; i++) {
                hash[i] = 1;
            }
            for (int i = 2; i<=sq; i++) {
                if (hash[i] == 0) {
                    continue;
                }
                //for (int j=i; j<n; j+=1) {
                for (int m = i*i; m<n; m+=i) {
                    hash[m] = 0;
                    // cout << "mark "<< i*j << " off" << endl;
                }
            }
        }

        int countPrimes2(int n) {
            int count = 0;
            for (int i=2; i<n; i++) {
                if (isPrime(i)) {
                    count ++;
                }
            }
            return count;
        }

        bool isPrime(int n) {
            if (n == 2 || n == 3) {
                return true;
            }
            for (int i=2; i <=(int)sqrt(n) ; i++) {
                if (n % i == 0) {
                    return false;
                }
            }

            return true;
        }
};

int main() {
    Solution o;
    {
        cout << o.countPrimes(4) << endl;  // 2
        cout << o.countPrimes(10) << endl;     // 4 
        cout << o.countPrimes(100) << endl;    // 25
        cout << o.countPrimes(1000) << endl;   // 168
        cout << o.countPrimes(999983) << endl; // 78497
    }

    return 0;
}
