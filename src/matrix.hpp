
/*
 *  matrix.hpp
 *  zhengshaoyin
 *  2015/0508
 *
 */

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <cstring>

#include <iostream>
#include <string>
#include <fstream>

namespace matrix_space
{
/**************************************************************/

template<typename T>
class matrix;

template<typename T>
std::ostream& operator<<(std::ostream& outs, matrix<T>& mat);
template<typename T>
std::istream& operator>>(std::istream& ins, matrix<T>& mat);

template<typename T>
matrix<T> transpose(matrix<T>& mat);
template<typename T>
matrix<T> operator+(matrix<T>& mat1, matrix<T>& mat2);
template<typename T>
matrix<T> operator-(matrix<T>& mat1, matrix<T>& mat2);
template<typename T>
matrix<T> operator*(matrix<T>& mat1, matrix<T>& mat2);

/**************************************************************/

template<typename T>
class matrix
{
public :
    matrix();
    matrix(size_t row_num, size_t col_num);
    matrix(const matrix<T>& mat);
    matrix<T>& operator=(const matrix<T>& mat);
    ~matrix();
public :
    size_t get_row_num();
    size_t get_col_num();
    T& at(size_t row, size_t col);
public :
    void read_file(std::string file_name);
    void write_file(std::string file_name);
    void resize(size_t row_num, size_t col_num);
    void reshape(size_t row_num, size_t col_num);
public :
    friend std::ostream& operator<<<>(std::ostream& outs, matrix<T>& mat);
    friend std::istream& operator>><>(std::istream& ins, matrix<T>& mat);


    friend matrix<T> transpose<>(matrix<T>& mat);
    friend matrix<T> operator+<>(matrix<T>& mat1, matrix<T>& mat2);
    friend matrix<T> operator-<>(matrix<T>& mat1, matrix<T>& mat2);
    friend matrix<T> operator*<>(matrix<T>& mat1, matrix<T>& mat2);
private :
    size_t row_num;
    size_t col_num;
    T* data;
};

/**************************************************************/

template<typename T>
matrix<T>::matrix()
{
    this->data = NULL;
    this->row_num = 256;
    this->col_num = 1;
    this->data = new T[this->row_num * this->col_num];
}
template<typename T>
matrix<T>::matrix(size_t row_num, size_t col_num)
{
    this->data = NULL;
    this->row_num = row_num;
    this->col_num = col_num;
    this->data = new T[this->row_num * this->col_num];
}
template<typename T>
matrix<T>::matrix(const matrix& mat)
{
    this->data = NULL;
    this->row_num = mat.row_num;
    this->col_num = mat.col_num;
    this->data = new T[this->row_num * this->col_num];
    memcpy(this->data, mat.data, this->row_num * this->col_num * sizeof(T));
}
template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& mat)
{
    if(this != &mat)
    {
        if(NULL != this->data)
        {
            delete [] this->data;
            this->data = NULL;
        }
        this->row_num = mat.row_num;
        this->col_num = mat.col_num;
        this->data = new T[this->row_num * this->col_num];
        memcpy(this->data, mat.data, this->row_num * this->col_num * sizeof(T));
    }
    return *this;
}
template<typename T>
matrix<T>::~matrix()
{
    if(NULL != this->data)
    {
        delete [] this->data;
        this->data = NULL;
    }
}

/**************************************************************/

template<typename T>
size_t matrix<T>::get_row_num()
{
    return this->row_num;
}
template<typename T>
size_t matrix<T>::get_col_num()
{
    return this->col_num;
}
template<typename T>
T& matrix<T>::at(size_t row, size_t col)
{
    return this->data[row * this->col_num + col];
}

/**************************************************************/

template<typename T>
void matrix<T>::resize(size_t row_num, size_t col_num)
{
    if(this->row_num * this->col_num == row_num * col_num)
    {
        this->row_num = row_num;
        this->col_num = col_num;
    }
    else
    {
        if(NULL != this->data)
        {
            delete [] this->data;
            this->data = NULL;
        }
        this->row_num = row_num;
        this->col_num = col_num;
        this->data = new T[this->row_num * this->col_num];
    }
}
template<typename T>
void matrix<T>::reshape(size_t row_num, size_t col_num)
{
    if(this->row_num * this->col_num == row_num * col_num)
    {
        this->row_num = row_num;
        this->col_num = col_num;
    }
}
template<typename T>
void matrix<T>::read_file(std::string file_name)
{
    std::ifstream ifs;
    ifs.open(file_name.c_str(), std::ios::binary);

    size_t row_num = 0;
    size_t col_num = 0;
    ifs.read((char*)&row_num, sizeof(size_t));
    ifs.read((char*)&col_num, sizeof(size_t));

    this->resize(row_num, col_num);
    ifs.read((char*)this->data, this->row_num * this->col_num * sizeof(T));

    ifs.close();
}
template<typename T>
void matrix<T>::write_file(std::string file_name)
{
    std::ofstream ofs;
    ofs.open(file_name.c_str(), std::ios::binary);

    ofs.write((char*)&this->row_num, sizeof(size_t));
    ofs.write((char*)&this->col_num, sizeof(size_t));
    ofs.write((char*)this->data, this->row_num * this->col_num * sizeof(T));

    ofs.close();
}

/**************************************************************/

template<typename T>
std::ostream& operator<<(std::ostream& outs, matrix<T>& mat)
{
    for(int i = 0; i < mat.row_num; ++i)
    {
        for(int j = 0; j < mat.col_num; ++j)
        {
            outs << mat.at(i, j) << " ";     // 1-D to 2-D
        }
        outs << endl;
    }
    return outs;
}
template<typename T>
std::istream& operator>>(std::istream& ins, matrix<T>& mat)
{
    for(int i = 0; i < mat.row_num * mat.col_num; ++i)
    {
        ins >> mat.data[i];
    }
    return ins;
}
template<typename T>
matrix<T> transpose(matrix<T>& mat)
{
    matrix<T> mat_result(mat.col_num, mat.row_num);

    for(int i = 0; i < mat_result.row_num; ++i)
    {
        for(int j = 0; j < mat_result.col_num; ++j)
        {
            mat_result.at(i, j) = mat.at(j, i);
        }
    }

    return mat_result;
}
template<typename T>
matrix<T> operator+(matrix<T>& mat1, matrix<T>& mat2)
{
    matrix<T> mat(mat1);
    if(mat1.row_num == mat2.row_num && mat1.col_num == mat2.col_num)
    {
        for(int i = 0; i < mat.row_num * mat.col_num; ++i)
        {
            mat.data[i] += mat2.data[i];
        }
    }
    return mat;
}
template<typename T>
matrix<T> operator-(matrix<T>& mat1, matrix<T>& mat2)
{
    matrix<T> mat(mat1);
    if(mat1.row_num == mat2.row_num && mat1.col_num == mat2.col_num)
    {
        for(int i = 0; i < mat.row_num * mat.col_num; ++i)
        {
            mat.data[i] -= mat2.data[i];
        }
    }
    return mat;
}
template<typename T>
matrix<T> operator*(matrix<T>& mat1, matrix<T>& mat2)
{
    matrix<T> mat(mat1.row_num, mat2.col_num);
    if(mat1.col_num == mat2.row_num)
    {
        for(int i = 0; i < mat.row_num; ++i)
        {
            for(int k = 0; k < mat.col_num; ++k)
            {
                T temp = 0;
                for(int j = 0; j < mat1.col_num; ++j)
                {
                    temp += mat1.at(i, j) * mat2.at(j, k);
                }
                mat.at(i, k) = temp;
            }
        }
    }
    return mat;
}

/**************************************************************/
}

#endif // MATRIX_HPP_INCLUDED
