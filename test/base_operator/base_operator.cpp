
/*
 *  main.cpp
 *  2015/05/08
 *
 */

#include <string>
#include <iostream>
using namespace std;

#include "../../src/matrix.hpp"
using namespace matrix_space;

int main()
{
    cout << "The sizeof(matrix) is:" << endl;
    cout << sizeof(matrix<float>) << endl;

    matrix<float> mat0(3, 3);
    cout << "Input a matrix of 3-by-3:" << endl;
    cin >> mat0;
    cout << "The matrix A is:" << endl;
    cout << mat0;

    cout << "The A.transpose() is:" << endl;
    cout << mat0.transpose();

    cout << "The A.rotate90() is:" << endl;
    cout << mat0.rotate90();

    cout << "The matrix (A + A) is:" << endl;
    cout << mat0 + mat0;

    cout << "The matrix (A - A)is:" << endl;
    cout << mat0 - mat0;

    cout << "The matrix A's elements sum is:" << endl;
    cout << mat0.sum() << endl;

    cout << "The matrix A's elements max is:" << endl;
    cout << mat0.max() << endl;

    cout << "The matrix A's elements min is:" << endl;
    cout << mat0.min() << endl;

    cout << "The matrix (A * A) is:" << endl;
    cout << mat0 * mat0.transpose();

    cout << "The matrix A reciprocal is:" << endl;
    cout << mat0.reciprocal();

    cout << "The matrix A sin is:" << endl;
    cout << mat0.sin();

    cout << "The matrix A cos is:" << endl;
    cout << mat0.cos();

    cout << "The matrix A exp is:" << endl;
    cout << mat0.exp();

    cout << "The matrix A sqrt is:" << endl;
    cout << mat0.sqrt();

    cout << "The matrix A log is:" << endl;
    cout << mat0.log();

    cout << "The matrix A^0.5 is:" << endl;
    cout << mat0.pow(0.5f);

    cout << "The matrix dot operator  (A .* A) is:" << endl;
    cout << mat0.dot('*', mat0);

    cout << "The matrix local_dot operator (A .+ one(2, 3)) in (1, 1) is:" << endl;
    cout << mat0.local_dot('+', matrix<float>::one(2, 2), 1, 1);

    cout << "The matrix A.get_local(0, 0, 2, 2) is:" << endl;
    cout << mat0.get_local(0, 0, 2, 2);

    cout << "The matrix (A * 7) is:" << endl;
    cout << mat0 * 7.0f;

    cout << "The matrix matrix<int>::eye(5) is:" << endl;
    cout << matrix<float>::eye(5);

    cout << "The matrix matrix<int>::zero(5, 7) is:" << endl;
    cout << matrix<float>::zero(5, 7);

    cout << "The matrix matrix<int>::one(5, 7) is:" << endl;
    cout << matrix<float>::one(5, 7);

    cout << "The matrix matrix<int>::random(4, 4, 0, 10) is:" << endl;
    matrix<float> random_mat = matrix<float>::random(4, 4, 0, 10);
    cout << random_mat;

    cout << "The matrix 's LU is:" << endl;
    matrix<float> P;
    matrix<float> L;
    matrix<float> U;
    if(random_mat.lu(P, L, U))
    {
        cout << "P:" << endl;
        cout << P;
        cout << "L:" << endl;
        cout << L;
        cout << "U:" << endl;
        cout << U;
    }
    else
    {
        cout << "Can not LU!" << endl;
    }

    cout << "The matrix det is:" << endl;
    cout << random_mat.det() << endl;

    cout << "The matrix inverse is:" << endl;
    cout << random_mat.inverse();

    string filename;
    cout << "Input file name to save the matrix:" << endl;
    cin >> filename;
    mat0.write_file(filename);
    cout << "The matrix A has be saved to file." << endl;

    matrix<float> mat1;
    mat1.read_file(filename);
    cout << "The matrix read from file is:" << endl;
    cout << mat1;

    return 0;
}
