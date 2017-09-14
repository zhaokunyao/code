#include <unistd.h>
#include <string.h>
class Worker {
    public:
        void operator()(bool is_write, int id) {
            init(is_write);
            go(id);
        }

        void init(bool is_write) {
            if (is_write) {
                std::cout << "change _count to ";
                strcpy(_count, "write");
                _count[6] = '\0';
                std::cout << "::::" << std::string(_count) << std::endl;
            }
        }

        void go(int id) {
            std::cout << id << " sleep 10" << std::endl;
            sleep(10);
            std::cout << id << ":_count:" << std::string(_count) << std::endl;
            sleep(100);
        }

    private: 
        char _count[12];
};
