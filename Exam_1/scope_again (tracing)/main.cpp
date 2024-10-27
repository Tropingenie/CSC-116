/* scope_again.cpp

   Exercise: Determine the output of this program without running it.

   B. Bird - 10/01/2019
*/

#include <iostream>

int x  {1};

void f1(){
    std::cout << "(In f1) x = " << x << std::endl;
    x = x + 1;
}
void f2(){
    int x  {1000};
    std::cout << "(In f2) x = " << x << std::endl;
    x = x + 10000;
}
int main(){
    int x  {6};
    int y {10};
    std::cout << "(In main) x = " << x << std::endl;
    f1();
    f2();
    f1();
    f2();
    if (0 < 1){
        int x {-10};
        std::cout << "(In if-statement) y = " << y << std::endl;
        std::cout << "(In if-statement) x = " << x << std::endl;
        x = 1000000000;
    }
    std::cout << "(In main) x = " << x << std::endl;
    return 0;
}