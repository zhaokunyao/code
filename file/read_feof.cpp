#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

class Solution {
    public:
    void read_feof(string filename) {
        FILE * fp = fopen(filename.c_str(), "r");
        if (!fp) {
            cout << " fp not ok " << endl;
        }
        char buf[2000];
        while (true) {
            while (fgets(buf, 1024, fp) != NULL) {
                cout << string(buf);
                cout << "============" << endl;
            }
            cout << "get end and sleep" << endl;
            sleep(10);
        }
    }
};

int main() {
    Solution o;
    o.read_feof("./a.txt");
    return 0;
}
