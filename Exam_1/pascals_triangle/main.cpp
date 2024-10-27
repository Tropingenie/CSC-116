/* pascals_triangle.cpp

   Pascal's Triangle is a way of computing binomial coefficients in a tabular form.
   Each entry (i,j), where i is the row number and j is the column number, can be computed
   as follows.
    - For all rows i, entry (i,0) = 1
    - For all rows i, entry (i,i) = 1
    - Each row i has i+1 elements (so there is no entry (i, i+1), for example)
    - For all columns j where 0 < j < i, entry (i,j) is computed as
        Entry(i,j) = Entry(i-1,j) + Entry(i-1,j-1)

   Task: Complete the code below to construct the first 10 rows of Pascal's triangle
         using a jagged 2d vector.

   B. Bird - 09/30/2019
*/

#include <iostream>
#include <vector>

using Triangle = std::vector< std::vector<int> >;


int main(){

    Triangle pascal {};


    /* Put your code here */
    //initialise all the vectors in Triangle
    std::vector<int> vec_one{1};
    for (int q {0}; q < 10; q++){
        pascal.push_back(vec_one);
        vec_one.push_back(1);
    }
    //Now we have a Triangle of all 1's

    //Compute the inner stuff:
    //We can start at (1,1) since the 0th row of the 0th column is just 1, which is already initialised
    unsigned int i = 1;
    unsigned int j = 1;
    for (i = 1; i < pascal.size(); i++){//parse through every row of Pascal we care about
        for (j = 1; j < i; j++){
            //Entry(i,j) = Entry(i-1,j) + Entry(i-1,j-1)
            auto& entryij = pascal.at(i).at(j), entryi1j = pascal.at(i-1).at(j), entryi1j1 = pascal.at(i-1).at(j-1);
            entryij = entryi1j + entryi1j1;
        }
    }

    //Print out the triangle (don't modify this)
    for(auto const& row: pascal){
        for(auto const& entry: row){
            std::cout << entry << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
