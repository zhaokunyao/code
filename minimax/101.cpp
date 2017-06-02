#include <iostream>
#include <map>
#include <vector>

using namespace std;
class Solution {
    public:
        vector<bool> used;
        map<int, bool> cache;

        int maxChoosableInteger;
        bool canIWin(int maxChoosableInteger, int desiredTotal) {
            cache.clear();
            used.resize(0);

            this->maxChoosableInteger = maxChoosableInteger;
            if (desiredTotal <= 0) {
                return true;
            }

            int sum = 0;
            for (int i =1; i<=maxChoosableInteger; i++) {
                sum += i;
            }
            if (sum < desiredTotal) {
                return false;
            }

            used.push_back(true);
            for (int i=1; i<=maxChoosableInteger; i++) {
                used.push_back(false);
            }
            return play(desiredTotal);
        }

        bool play(int desiredTotal) {

            // <=0 对方其实在上一步已经获胜了
            if (desiredTotal <= 0) {
                return false;
            }


            // 缓存
            int key = getCacheKey();
            if (cache.count(key) > 0) {
                return cache[key];
            }

            // 遍历每一种情况
            for (int i =1; i <= maxChoosableInteger; i++) {

                if (used[i]) {
                    continue;
                }

                used[i] = true;

                //the other player failed
                if (play(desiredTotal-i) == false) {
                    // 是的，这里要把used[i]设置为false.
                    used[i] = false;
                    // int key = getCacheKey();
                    cache[key] = true;
                    return true;
                }
                used[i] = false;
            }

            cache[key] = false;
            return false;
        }

        int getCacheKey() {
            int n = 0;
            for (int i=1; i<=maxChoosableInteger; i++) {
                n = n * 2 + used[i];
            }
            return n;
        }
};

int main() {
    Solution * o = new Solution();
    {
        int maxChoosableInteger = 5;
        int desiredTotal        = 50;
        cout << maxChoosableInteger << ":" << desiredTotal << ":" << o->canIWin(maxChoosableInteger, desiredTotal) << endl;
    }
    {
        int maxChoosableInteger = 10;
        int desiredTotal        = 11;
        cout << maxChoosableInteger << ":" << desiredTotal << ":" << o->canIWin(maxChoosableInteger, desiredTotal) << endl;
    }
    {
        int maxChoosableInteger = 10;
        int desiredTotal        = 40;
        cout << maxChoosableInteger << ":" << desiredTotal << ":" << o->canIWin(maxChoosableInteger, desiredTotal) << endl;
    }
    {
        int maxChoosableInteger = 10;
        int desiredTotal        = 10;
        cout << maxChoosableInteger << ":" << desiredTotal << ":" << o->canIWin(maxChoosableInteger, desiredTotal) << endl;
    }
    return 0;
}
