#include <iostream>
#include <gtest/gtest.h>
#include "../include/algebra.h"
using namespace algebra;
int main(int argc, char **argv)
{
    if (false) // Set to false to run unit-tests
    {
        Matrix mat1{{1,1,1},{1,2,-1},{2,3,4}};
        Matrix mat2 = inverse(mat1);
        Matrix res = multiply(mat1, mat2);
        display(res); 
        // Debug section: Place your debugging code here
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}