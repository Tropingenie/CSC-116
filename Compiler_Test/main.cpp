#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers {1, 2, 3, 4, 5};

    int sum {};
    for(auto n: numbers) {
        sum += n;
    }
    std::cout << "The sum is " << sum << std::endl;
    return 0;
}