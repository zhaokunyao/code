
#include <iostream>
#include <limits.h>
#include <map>
#include <vector>
using namespace std;

int bigger(vector<int> &A, int i, int j) {
    int len = A.size();
    int count = 0;
    for (; j < len; j++) {
        if (A[j] > A[i]) {
            count ++;
        }
    }
    return count;
}


int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    int len = A.size();
    int count = 0;
    int incr_count = 0;
    for (int i = 0; i< len-1; i++) {
        if (i >=1 && A[i] > A[i-1]) {
            incr_count ++;
        } else {
            incr_count = 0;
        }
        count += (incr_count + 1) * bigger(A, i, i+1);
    }
    return count;
}

int main() {
    {
        vector<int> A = {1,2,3,4};
        cout << solution(A)<< endl;
    }
    {
        vector<int> A = {};
        cout << solution(A)<< endl;
    }
    {
        vector<int> A = {4,6,7,3,2,7};
        cout << solution(A)<< endl;
    }
    return 0;
}

