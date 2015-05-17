
/*
 *  main.cpp
 *  zhengshaoyin
 *  2015/0508
 *
 */

#include <iostream>
using namespace std;

#include "../../src/matrix.hpp"
using namespace matrix_space;

int main()
{
    matrix<int> mat1(2, 3);
    cout << "Input a matrix of 2-by-3 :" << endl;
    cin >> mat1;
    cout << "The matrix A is :" << endl;
    cout << mat1;

    matrix<int> mat2;
    mat2 = transpose(mat1);
    cout << "The transposed A is :" << endl;
    cout << mat2;

    matrix<int> mat3 = mat1 + mat1;
    cout << "The matrix (A + A) is :" << endl;
//    cout << mat3;
    cout << mat1 + mat1;

    matrix<int> mat4 = mat1 - mat1;
    cout << "The matrix (A - A)is :" << endl;
    cout << mat1 - mat1;

    matrix<int> mat5 = mat1 * mat2;
    cout << "The matrix (A * A) is :" << endl;
    cout << mat1 * mat2;

    mat1.write_file("mat1.txt");
    cout << "The matrix A has be saved to file. " << endl;

    matrix<int> mat6;
    mat6.read_file("mat1.txt");
    cout << "The matrix read from file is :" << endl;
    cout << mat6;

    matrix<int> mat7;
    mat7 = dot('*', mat1, mat6);
    cout << "The matrix dot operator  (A .* A) is :" << endl;
    cout << mat7;

//    matrix<int> mat8(mat1);
//    mat8 *= 7;
    matrix<int> mat8;
    mat8 = mat1 * 7;
    cout << "The matrix (A * 7) is :" << endl;
    cout << mat8;

    matrix<int> mat9(7, 7);
    mat9.eye(5);
    cout << "The matrix A.eye is :" << endl;
    cout << mat9;

    return 0;
}
