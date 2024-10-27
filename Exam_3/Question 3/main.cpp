#include <iostream>
class BaseClass{
public:
    BaseClass() { }
    void a_method(){
        std::cout << "BaseClass A" << std::endl;
    }
    virtual void another_method(){
        std::cout << "BaseClass B" << std::endl;
    };
};
class DerivedClass: public BaseClass{
public:
    DerivedClass() { }
    void a_method(){
        std::cout << "DerivedClass A" << std::endl;
    }
};
void F(BaseClass& Z){
    Z.a_method();
    Z.another_method();
}
void G(DerivedClass& Z){
    Z.a_method();
    Z.another_method();
}
int main(){
    BaseClass x;
    DerivedClass y;
    F(x);
    F(y);
    G(y);
    return 0;
}
