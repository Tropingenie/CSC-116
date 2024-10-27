#include <iostream>
#include <string>
#include <vector>
#include <functional>
/* foreach_if: Given a vector vec, a condition and a function F, 6 run F on all elements of the vector where the 7 condition evaluates to true. */
template<typename T>
void foreach_if( std::vector<T>& vec, std::function< bool(T) > condition,
        std::function< void(T) > F ){
    for(auto x: vec){
        if (condition(x))
            F(x);
    }
}
/*Code below written by Benjamin Lyne*/
template <typename T>
void foreach_ifnot(std::vector<T>& vec, std::function< bool(T) > condition,
        std::function< void(T) > F){
    auto y = [condition](int x){
        return !condition(x);
    };
    foreach_if<T>(vec, y, F);
};
std::vector<int> filter_element(std::vector<int>& vec, int z){
    std::vector<int> new_vec{};
    auto F = [&new_vec, vec, z](int i){
      new_vec.push_back(i);
    };
    auto C = [&](int i){
      if (i!=z) return true;
      else return false;
    };
    foreach_if<int>(vec, C, F);
    return new_vec;
};
/*Code above written by Benjamin Lyne*/
int main(){
    std::vector<int> Vi {10, 6, -6, 10, 100, 17};
    std::vector<std::string> Vs {"Victoria","Vancouver","Duncan","Sidney"};
    int sum = 0;
    auto Ci = [](int x){
        return x > 0 && x <= 10;
    };
    auto Fi = [&](int x){
        sum += x;
    };
    auto Cs = [](std::string s){
        return s.length() <= 6;
    };
    auto Fs = [&](std::string s){
        sum += s.length();
    };
    foreach_if<int>(Vi, Ci, Fi);
    std::cout << "Sum (1): " << sum << std::endl;
    foreach_if<std::string>(Vs, Cs, Fs);
    std::cout << "Sum (2): " << sum << std::endl;
    sum = 0;
    foreach_ifnot<int>(Vi, Ci, Fi);
    std::cout << "Sum (3): " << sum << std::endl;
    auto new_vec = filter_element(Vi, 6);
    for (auto x: new_vec){ std::cout << x << std::endl;}//this loop just prints the vector
    return 0;
}