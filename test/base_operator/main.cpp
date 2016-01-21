
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
    matrix<int> mat0(3, 3);
    cout << "Input a matrix of 3-by-3 :" << endl;
    cin >> mat0;
    cout << "The matrix A is :" << endl;
    cout << mat0;

    cout << "The A.transpose() is :" << endl;
    cout << mat0.transpose();

    cout << "The A.rotate90() is :" << endl;
    cout << mat0.rotate90();

    cout << "The matrix (A + A) is :" << endl;
    cout << mat0 + mat0;

    cout << "The matrix (A - A)is :" << endl;
    cout << mat0 - mat0;

    cout << "The matrix A's elements sum is :" << endl;
    cout << mat0.elem_sum() << endl;

    cout << "The matrix (A * A) is :" << endl;
    cout << mat0 * mat0.transpose();

    cout << "The matrix dot operator  (A .* A) is :" << endl;
    cout << mat0.dot('*', mat0);

    cout << "The matrix local_dot operator (A .+ one(2, 3)) in (1, 1) is :" << endl;
    cout << mat0.local_dot('+', matrix<int>::one(2, 2), 1, 1);

    cout << "The matrix A.get_local(0, 0, 2, 2) is :" << endl;
    cout << mat0.get_local(0, 0, 2, 2);

    cout << "The matrix (A * 7) is :" << endl;
    cout << mat0 * 7;

    cout << "The matrix matrix<int>::eye(5) is :" << endl;
    cout << matrix<int>::eye(5);

    cout << "The matrix matrix<int>::zero(5, 7) is :" << endl;
    cout << matrix<int>::zero(5, 7);

    cout << "The matrix matrix<int>::one(5, 7) is :" << endl;
    cout << matrix<int>::one(5, 7);

    cout << "The matrix matrix<int>::random(5, 7, 0, 10) is :" << endl;
    cout << matrix<int>::random(5, 7, 0, 10);

    mat0.write_file("mat0.txt");
    cout << "The matrix A has be saved to file. " << endl;

    matrix<int> mat1;
    mat1.read_file("mat0.txt");
    cout << "The matrix read from file is :" << endl;
    cout << mat1;

    return 0;
}
