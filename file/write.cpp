#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // int fd = open("/tmp/aaaaaaa", O_RDWR|O_APPEND|O_CREAT); // ---xrwx--T
    int fd = open("/tmp/aaaaaaa", O_WRONLY|O_APPEND|O_CREAT); // -rwx--x---
    write(fd, "abce\n", 5);
    char log[1000];

    double x0 = 1000000;
    double y0 = 2000000;
    double x1 = 1111111;
    double y1 = 2222222;
    double a  = 3.24;
    int n = sprintf(log, "zhaokunyao cal distance: %f, %f, %f, %f, dis:%f\n", x0, y0, x1, y1, a);
    write(fd, log, n);
    fsync(fd);
    close(fd);
}
