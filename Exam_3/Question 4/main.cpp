#include <iostream>
#include <memory>
class Z{
public:
    Z(int val): value {val} {
        std::cout << "Z constructor: " << value << std::endl;
    }
    ~Z(){
        std::cout << "Z destructor: " << value << std::endl;
    }
private:
    int value;
};
class ZPair{
public:
    ZPair(){
        right_z = std::make_shared<Z>(6);
        left_z = std::make_shared<Z>(10);
    }
    void go(){
        left_z = nullptr;
        right_z = nullptr;
        left_z = std::make_shared<Z>(187);
    }
    std::shared_ptr<Z> left_z, right_z;
};
int main(){
    ZPair zp;
    std::cout << "main (1)" << std::endl;
    zp.go();
    std::cout << "main (2)" << std::endl;
    return 0;
}