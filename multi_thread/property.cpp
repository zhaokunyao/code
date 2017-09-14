#include <iostream>
#include <thread>
#include <vector>

#include "worker.h"
#include <unistd.h>

int main() {
    Worker wf;
    std::vector<std::thread> worker_threads;
    std::cout << "start 1" << std::endl;
    worker_threads.push_back(std::thread(wf, false, 1));

    sleep(2);
    std::cout << "start 2 " << std::endl;
    worker_threads.push_back(std::thread(wf, true, 2));
    sleep(2);
    std::cout << "start 3 " << std::endl;
    worker_threads.push_back(std::thread(wf, false, 3));
    sleep(5000);
}
