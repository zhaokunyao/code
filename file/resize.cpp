#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

class Solution {
    public:
    void resize(string filename) {
        int fd  =  open(filename.c_str(), 2);   // 读写
        ftruncate(fd, 20);
    }
};


int main() {
    Solution * o = new Solution();
    o->resize("./foo");
    return 0;
}
