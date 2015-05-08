
/*
 *  test.cpp
 *  zhengshaoyin
 *  2015/0508
 *
 */

#include <iostream>
using namespace std;

#include "../src/matrix.hpp"
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
    cout << mat3;

    matrix<int> mat4 = mat1 - mat1;
    cout << "The matrix (A - A)is :" << endl;
    cout << mat4;

    matrix<int> mat5 = mat1 * mat2;
    cout << "The matrix (A * A) is :" << endl;
    cout << mat5;

    mat1.write_file("A.txt");
    cout << "The matrix A has be saved to file. " << endl;

    matrix<int> mat6;
    mat6.read_file("A.txt");
    cout << "The matrix read from file is :" << endl;
    cout << mat6;

    return 0;
}
