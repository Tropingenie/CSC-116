/* multi_layer_catch.cpp

   B. Bird - 09/24/2019
*/
#include <vector>
#include <iostream>
#include <stdexcept>


int G(int i){
    std::cout << "G (1)" << std::endl;
    if (i < 0)
        throw std::domain_error("Negative values not allowed");
    std::cout << "G (2)" << std::endl;
    if (i > 0)
        throw std::runtime_error("Positive values definitely not allowed");
    std::cout << "G (3)" << std::endl;
    return 6;
}

void F(){
    std::cout << "F (1)" << std::endl;
    auto x = 1000;
    x = G(0);
    try{
        x = G(-1);
        std::cout << "F (2)" << std::endl;
    }catch(std::domain_error e){
        std::cout << "F: Caught domain error" << std::endl;
    }
    std::cout << "F (3)" << std::endl;
    try{
        x = G(1);
        std::cout << "F (4)" << std::endl;
    }catch(std::domain_error e){
        std::cout << "F: Caught domain error" << std::endl;
    }
    std::cout << "F (5)" << std::endl;
}


int main(){

    try{
        std::cout << "main (1)" << std::endl;
        F();
        std::cout << "main (2)" << std::endl;
        throw std::runtime_error("Out of patience");
        std::cout << "main (3)" << std::endl;
    }catch( std::runtime_error e ){
        std::cout << "main: Caught a runtime_error: " << e.what() << std::endl;
    }catch( std::domain_error e ){
        std::cout << "main: Caught a domain_error: " << e.what() << std::endl;
    }catch(...){
        //A catch block with a '...' filter will catch anything
        //(and since the type is indeterminate, it is not permitted to name and
        // use the caught object)
        std::cout << "main: Caught... something?" << std::endl;
    }
    std::cout << "main (4)" << std::endl;
    return 0;

}