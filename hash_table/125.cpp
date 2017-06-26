#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
#include <set>
using namespace std;

class RandomizedSet {
    public:
        vector<int> vec;
        map<int, int> hash;
        /** Initialize your data structure here. */
        RandomizedSet() {
            vec.clear();
            hash.clear();
        }

        /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
        bool insert(int val) {
            if (hash.find(val) != hash.end()) {
                return false;
            }
            vec.push_back(val);
            hash[val]  = vec.size() - 1;
            return true;
        }

        /** Removes a value from the set. Returns true if the set contained the specified element. */
        bool remove(int val) {
            if (hash.find(val) == hash.end()) {
                return false;
            }

            if (hash[val] == vec.size() -1) {
                hash.erase(val);
                vec.pop_back();
                return true;
            }

            int last_val    = vec.back();
            hash[last_val]  = hash[val];
            std::swap(vec[hash[val]], vec[vec.size()-1]);
            hash.erase(val);
            vec.pop_back();
            return true;
        }

        /** Get a random element from the set. */
        int getRandom() {
            return vec[rand() % vec.size()];
        }

        void printVec() {
            for (auto && n: vec) {
                cout << n << ", ";
            }
            cout << endl;
        }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

int main() {
    RandomizedSet * obj = new RandomizedSet();
    {
        int val = 0;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        val = 0;
        cout << "remove " << val << ":" << obj->remove(val) << endl;
        obj->printVec();
        val = -1;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        val = 0;
        cout << "remove " << val << ":" << obj->remove(val) << endl;
        obj->printVec();
        cout << obj->getRandom() << endl;
        cout << obj->getRandom() << endl;
    }
    {
        int val = 10;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        val = 20;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        val = 10;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        val = 30;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        val = 10;
        cout << "remove " << val << ":" << obj->remove(val) << endl;
        val = 10;
        cout << "remove " << val << ":" << obj->remove(val) << endl;
        val = 10;
        cout << "insert " << val << ":" << obj->insert(val) << endl;
        cout << "random: " << obj->getRandom() << endl;
        val = 30;
        cout << "remove " << val << ":" << obj->remove(val) << endl;
        obj->printVec();
        cout << "random: " << obj->getRandom() << endl;
        cout << "random: " << obj->getRandom() << endl;
        cout << "random: " << obj->getRandom() << endl;
        cout << "random: " << obj->getRandom() << endl;
        cout << "random: " << obj->getRandom() << endl;
        cout << "random: " << obj->getRandom() << endl;
    }

    return 0;
}
