
/*
 *  matrix.hpp
 *  zhengshaoyin
 *  2015/05/08
 *
 */

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <cstring>

#include <iostream>
#include <string>
#include <fstream>

#include "base_matrix.hpp"
#include "base_operator.hpp"

namespace matrix_space
{
/**************************************************************/

template<typename T>
class matrix : public base_matrix<T>
{
public :
    matrix();
    matrix(size_t row_num, size_t col_num);
    matrix(const matrix<T>& mat);
    matrix<T>& operator=(const matrix<T>& mat);
    ~matrix();
public :
    void read_file(std::string file_name);
    void write_file(std::string file_name);
    void resize(size_t row_num, size_t col_num);
    void reshape(size_t row_num, size_t col_num);
    void fill(const T& value);
    void eye(size_t n);
public :
    void operator+=(const matrix<T>& mat);
    void operator-=(const matrix<T>& mat);
    void operator*=(const matrix<T>& mat);
    void operator+=(const T& value);
    void operator-=(const T& value);
    void operator*=(const T& value);
};

/**************************************************************/

template<typename T>
matrix<T>::matrix() : base_matrix<T>()
{
}
template<typename T>
matrix<T>::matrix(size_t row_num, size_t col_num) : base_matrix<T>(row_num, col_num)
{
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
template<typename T>
void matrix<T>::fill(const T& value)
{
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            this->at(i, j) = value;
        }
    }
}
template<typename T>
void matrix<T>::eye(size_t n)
{
    this->resize(n, n);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            if(i == j)
            {
                this->at(i, j) = 1;
            }
            else
            {
                this->at(i, j) = 0;
            }
        }
    }
}

/**************************************************************/

template<typename T>
void matrix<T>::operator+=(const matrix<T>& mat)
{
    if(this->row_num == mat.get_row_num() && this->col_num == mat.get_col_num())
    {
        for(int i = 0; i < this->row_num; ++i)
        {
            for(int j = 0; j < this->col_num; ++j)
            {
                this->at(i, j) += mat.at(i, j);
            }
        }
    }
}
template<typename T>
void matrix<T>::operator-=(const matrix<T>& mat)
{
    if(this->row_num == mat.get_row_num() && this->col_num == mat.get_col_num())
    {
        for(int i = 0; i < this->row_num; ++i)
        {
            for(int j = 0; j < this->col_num; ++j)
            {
                this->at(i, j) -= mat.at(i, j);
            }
        }
    }
}
template<typename T>
void matrix<T>::operator*=(const matrix<T>& mat)
{
    matrix<T> mat_temp(this->row_num, mat.col_num);
    if(this->col_num == mat.row_num)
    {
        for(int i = 0; i < this->row_num; ++i)
        {
            for(int k = 0; k < mat.col_num; ++k)
            {
                T temp = 0;
                for(int j = 0; j < this->col_num; ++j)
                {
                    temp += this->at(i, j) * mat.at(j, k);
                }
                mat_temp.at(i, k) = temp;
            }
        }
    }
    (*this) = mat_temp;
}

template<typename T>
void matrix<T>::operator+=(const T& value)
{
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            this->at(i, j) += value;
        }
    }
}
template<typename T>
void matrix<T>::operator-=(const T& value)
{
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            this->at(i, j) -= value;
        }
    }
}
template<typename T>
void matrix<T>::operator*=(const T& value)
{
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            this->at(i, j) *= value;
        }
    }
}

/**************************************************************/
}

#endif // MATRIX_HPP_INCLUDED
