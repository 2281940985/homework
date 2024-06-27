#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../include/algebra.h"
using namespace algebra;
TEST(Algebra, ZEROS)
{
    Matrix mat{zeros(5,6)};
    EXPECT_EQ(mat.size(),5);
    EXPECT_EQ(mat[0].size(),6);
    for(const auto &row:mat)
    {
        for(const auto &elem:row)
        {
            EXPECT_EQ(elem,0);
        }
    }
}
TEST(Algebra, ONES)
{
    Matrix mat{ones(5,6)};
    EXPECT_EQ(mat.size(),5);
    EXPECT_EQ(mat[0].size(),6);
    for(const auto &row:mat)
    {
        for(const auto &elem:row)
        {
            EXPECT_EQ(elem,1);
        }
    }
}
TEST(Algebra, IDENTITY)
{
    Matrix mat{identity(5)};
    EXPECT_EQ(mat.size(),5);
    EXPECT_EQ(mat[0].size(),5);
    for(int i=0;i<5;i++)
    {
        EXPECT_EQ(mat[i][i],1);
    }
}
TEST(Algebra, RANDON)
{
    Matrix mat{randon(5, 6, 0, 100)};
    EXPECT_EQ(mat.size(),5);
    EXPECT_EQ(mat[0].size(), 6);
    for(const auto &row:mat)
    {
        for(const auto &ele : row)
        {
            EXPECT_GT(ele, 0);
            EXPECT_LT(ele, 100);
        }
    }
}
TEST(Algebra, SUM_SUB)
{
    Matrix mat1{{1,2},{3,4}};
    Matrix mat2{{5,6},{7,8}};
    Matrix mat_sum = sum_sub(mat1,mat2, "1123");
    Matrix mat_res1 = {{6,8},{10,12}};
    Matrix mat_sub = sum_sub(mat1,mat2, "sub");
    for(int i = 0; i < mat_sum.size(); i++)
    {
        for(int j = 0; j < mat_sum[i].size(); j++)
        {
            EXPECT_EQ(mat_sum[i][j], mat_res1[i][j]);
            EXPECT_EQ(mat_sub[i][j], mat1[i][j] - mat2[i][j]);
        }
    }
    
}
TEST(Algebra, MULTIPLY_NUM)
{
    Matrix mat1{{1,2},{3,4}, {5,6}};
    Matrix mat =  multiply(mat1, 2);
    EXPECT_EQ(mat.size(), 3);
    EXPECT_EQ(mat[0].size(), 2);
    for(int i = 0; i < mat.size(); i++)
    {
        for(int j = 0; j < mat[i].size(); j++)
        {
            EXPECT_EQ(mat[i][j], mat1[i][j] * 2);
        }
    }
}
TEST(Algebra, MULTIPLY_MAT)
{
    Matrix mat1{{1,2},{3,4}, {5,6}};
    Matrix mat2{{1,2},{3,4}};
    Matrix mat = multiply(mat1, mat2);
    EXPECT_EQ(mat.size(), 3);
    EXPECT_EQ(mat[0].size(), 2);
    for(int i = 0; i < mat.size(); i++)
    {
        for(int j = 0; j < mat[i].size(); j++)
        {
            EXPECT_EQ(mat[i][j], mat1[i][0] * mat2[0][j] + mat1[i][1] * mat2[1][j]);
        }
    }
}
TEST(Algebra, HANDAMARD_OUT)
{
    Matrix mat1{{1,2},{3,4}};
    Matrix mat2{{5,6},{7,8}};
    Matrix mat = handamard_product(mat1, mat2);
    EXPECT_EQ(mat.size(), mat1.size());
    EXPECT_EQ(mat[0].size(), mat1[0].size());
    for(int i = 0; i < mat.size(); i++)
    {
        for(int j = 0; j < mat[0].size(); j++)
        {
            EXPECT_EQ(mat[i][j], mat1[i][j] * mat2[i][j]);
        }
    }
}
TEST(Algebra, TRANSPOSE)
{
    Matrix mat1{{1,2},{3,4}};
    Matrix mat = transpose(mat1);
    EXPECT_EQ(mat.size(), mat1[0].size());
    EXPECT_EQ(mat[0].size(), mat1.size());
    for(int i = 0; i < mat.size(); i++)
    {
        for(int j = 0; j < mat[0].size(); j++)
        {
            EXPECT_EQ(mat[i][j], mat1[j][i]);
        }
    }
}
TEST(Algebra, TRACE)
{
    Matrix mat1{{1,2,3},{3,4,5},{4,5,6}};
    int tr = trace(mat1);
    int sum = 0;
    for(int i = 0; i < mat1.size(); ++i)
    {
        sum += mat1[i][i];
    }
    EXPECT_EQ(tr, sum);
}
TEST(Algebra, DETERMINANT)
{
    Matrix mat1{{1,2,3},{3,4,5},{3,4,5}};
    double det1 = determinant(mat1);
    EXPECT_EQ(det1, 0);
    Matrix mat2{{1,1,1},{3,4,5},{4,5,6}};
    double det2 = determinant(mat2);
    EXPECT_EQ(det2, 0);
    Matrix mat3{{1,1,1},{1,2,-1},{2,3,4}};
    double det3 = determinant(mat3);
    EXPECT_EQ(det3, 4);
}
TEST(Algebra, INVERSE)
{
    Matrix mat1{{1,1,1},{1,2,-1},{2,3,4}};
    Matrix mat2 = inverse(mat1);
    EXPECT_EQ(mat2.size(), mat1.size());
    EXPECT_EQ(mat2[0].size(), mat1[0].size());
    Matrix mat3 = multiply(mat1, mat2);
    for(int i = 0; i < mat3.size(); i++)
    {
        for(int j = 0; j < mat3[0].size(); j++)
        {
            if(i == j)
            {
                EXPECT_EQ(mat3[i][j], 1);
            }
            else
            {
                EXPECT_EQ(mat3[i][j], 0);
            }
        }
    }
}
