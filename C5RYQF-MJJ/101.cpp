#include <iostream>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    int sum = 0;
    for (auto n : A) {
        sum += n;
    }

    int s = 0;
    int i =0;
    for (auto n: A) {
        s += n;
        i ++;
        if (s-n == (sum-n) /2) {
            return i;
        }
    }

    return -1;
}

int main(){
    {
        vector<int> A = {-7, 1, 5, 2, -4, 3, 0};
        cout << solution(A) << endl;
    }
    {
        vector<int> A = {1, 2,1}; 
        cout << solution(A) << endl;
    }
    return 0;
}
