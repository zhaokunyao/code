#include <iostream>
using namespace std;

class A
{
public:
    int a;
    A(int a)
    {
        this->a = a;
        cout << "construct A(a)" << endl;
    }
    A(): x(10), y(11), z(12)
    {
        this->a = 0;
        cout << "construct A()" << endl;
    }
protected:
    int x;
    int y;
    int z;
};

class B : public A
{
public:
    int b;
    /**
    B(int b)
    {
        this ->b = b;
        cout << "construct B(b)" << endl;
    }
    **/
    // B(): x(50), y(60), z(70)
    B(): x(50), y(60), z(70)
    {
        cout << "construct B()" << endl;
    }
    void o() {
        cout << x << y << z << endl;
    }
};

int main()
{
    B b;
    b.o();
    return 0;
}
