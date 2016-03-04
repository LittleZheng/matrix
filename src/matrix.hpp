
/*
 *  matrix.hpp
 *  zhengshaoyin
 *  2015/05/08
 *
 */

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <cstring>
#include <cstdlib>
#include <cmath>

#include <iostream>
#include <string>
#include <fstream>

#include "base_matrix.hpp"
#include "friend_func.hpp"

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
    static matrix<T> eye(size_t n);
    static matrix<T> zero(size_t row_num, size_t col_num);
    static matrix<T> one(size_t row_num, size_t col_num);
    static matrix<T> random(size_t row_num, size_t col_num, const T& range_low = (T)-1.0, const T& range_high = (T)1.0);
public :
    void resize(size_t row_num, size_t col_num);
    void reshape(size_t row_num, size_t col_num);
    void fill(const T& value);
    T sum();    // All elements add up.
    T max(size_t& row, size_t& col);
    T max();
    T min(size_t& row, size_t& col);
    T min();
    matrix<T> transpose();
    matrix<T> rotate90();
    matrix<T> inverse();
    matrix<T> sin();
    matrix<T> cos();
    matrix<T> exp();
    matrix<T> sqrt();
    matrix<T> log();
    matrix<T> pow(const T& exponent);
    matrix<T> dot(char op, const matrix<T>& mat);
    matrix<T> local_dot(char op, const matrix<T>& mat, size_t row, size_t col); // The size of mat should be less than *this's.
    matrix<T> get_local(size_t row, size_t col, size_t row_num, size_t col_num);
    T* get_data() const;
    bool lu(matrix<T>& L, matrix<T>& U);
public :
    void operator+=(const matrix<T>& mat);
    void operator-=(const matrix<T>& mat);
    void operator*=(const matrix<T>& mat);
    void operator+=(const T& value);
    void operator-=(const T& value);
    void operator*=(const T& value);
public :
    void read_file(std::string file_name);
    void write_file(std::string file_name);

    friend std::ostream& operator<< <T>(std::ostream& outs, const matrix<T>& mat);
    friend std::istream& operator>> <T>(std::istream& ins, matrix<T>& mat);
    friend matrix<T> operator+ <T>(const matrix<T>& mat1, const matrix<T>& mat2);
    friend matrix<T> operator- <T>(const matrix<T>& mat1, const matrix<T>& mat2);
    friend matrix<T> operator* <T>(const matrix<T>& mat1, const matrix<T>& mat2);
    friend matrix<T> operator+ <T>(const T& value, const matrix<T>& mat2);
    friend matrix<T> operator- <T>(const T& value, const matrix<T>& mat2);
    friend matrix<T> operator* <T>(const T& value, const matrix<T>& mat2);
    friend matrix<T> operator+ <T>(const matrix<T>& mat1, const T& value);
    friend matrix<T> operator- <T>(const matrix<T>& mat1, const T& value);
    friend matrix<T> operator* <T>(const matrix<T>& mat1, const T& value);
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
matrix<T> matrix<T>::eye(size_t n)
{
    matrix<T> mat_result(n, n);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(i == j)
            {
                mat_result.at(i, j) = (T)1.0;
            }
            else
            {
                mat_result.at(i, j) = (T)0.0;
            }
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::zero(size_t row_num, size_t col_num)
{
    matrix<T> mat_result(row_num, col_num);
    mat_result.fill((T)0.0);
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::one(size_t row_num, size_t col_num)
{
    matrix<T> mat_result(row_num, col_num);
    mat_result.fill((T)1.0);
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::random(size_t row_num, size_t col_num, const T& range_low, const T& range_high)
{
    matrix<T> mat_result(row_num, col_num);
    for(int i = 0; i < row_num; ++i)
    {
        for(int j = 0; j < col_num; ++j)
        {
            double temp = (double)rand() / (double)RAND_MAX;
            mat_result.at(i, j) = T(range_low + temp * (range_high - range_low));
        }
    }
    return mat_result;
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
T matrix<T>::sum()
{
    T result = (T)0.0;
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            result += this->at(i, j);
        }
    }
    return result;
}
template<typename T>
T matrix<T>::max(size_t& row, size_t& col)
{
    T max_elem = this->at(0, 0);
    row = 0;
    col = 0;
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            if(max_elem < this->at(i, j))
            {
                max_elem = this->at(i, j);
                row = i;
                col = j;
            }
        }
    }
    return max_elem;
}
template<typename T>
T matrix<T>::max()
{
    T max_elem = this->at(0, 0);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            if(max_elem < this->at(i, j))
            {
                max_elem = this->at(i, j);
            }
        }
    }
    return max_elem;
}
template<typename T>
T matrix<T>::min(size_t& row, size_t& col)
{
    T min_elem = this->at(0, 0);
    row = 0;
    col = 0;
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            if(min_elem > this->at(i, j))
            {
                min_elem = this->at(i, j);
                row = i;
                col = j;
            }
        }
    }
    return min_elem;
}
template<typename T>
T matrix<T>::min()
{
    T min_elem = this->at(0, 0);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            if(min_elem > this->at(i, j))
            {
                min_elem = this->at(i, j);
            }
        }
    }
    return min_elem;
}
template<typename T>
matrix<T> matrix<T>::transpose()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < mat_result.row_num; ++i)
    {
        for(int j = 0; j < mat_result.col_num; ++j)
        {
            mat_result.at(i, j) = this->at(j, i);
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::rotate90()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(j, this->row_num - (i+1)) = this->at(i, j);
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::inverse()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = (T)1 / this->at(i, j);
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::sin()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = std::sin(this->at(i, j));
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::cos()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = std::cos(this->at(i, j));
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::exp()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = std::exp(this->at(i, j));
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::sqrt()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = std::sqrt(this->at(i, j));
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::log()
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = std::log(this->at(i, j));
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::pow(const T& exponent)
{
    matrix<T> mat_result(this->col_num, this->row_num);
    for(int i = 0; i < this->row_num; ++i)
    {
        for(int j = 0; j < this->col_num; ++j)
        {
            mat_result.at(i, j) = std::pow(this->at(i, j), exponent);
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::dot(char op, const matrix<T>& mat)
{
    matrix<T> mat_result(*this);
    if(this->row_num == mat.row_num && this->col_num == mat.col_num)
    {
        switch(op)
        {
        case '+' :
            for(int i = 0; i < this->row_num; ++i)
            {
                for(int j = 0; j < this->col_num; ++j)
                {
                    mat_result.at(i, j) += mat.at(i, j);
                }
            }
            break;
        case '-' :
            for(int i = 0; i < this->row_num; ++i)
            {
                for(int j = 0; j < this->col_num; ++j)
                {
                    mat_result.at(i, j) -= mat.at(i, j);
                }
            }
            break;
        case '*' :
            for(int i = 0; i < this->row_num; ++i)
            {
                for(int j = 0; j < this->col_num; ++j)
                {
                    mat_result.at(i, j) *= mat.at(i, j);
                }
            }
            break;
        case '/' :
            for(int i = 0; i < this->row_num; ++i)
            {
                for(int j = 0; j < this->col_num; ++j)
                {
                    mat_result.at(i, j) /= mat.at(i, j);
                }
            }
            break;
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::local_dot(char op, const matrix<T>& mat, size_t row, size_t col)
{
    matrix<T> mat_result(*this);
    if(this->row_num >= row + mat.row_num && this->col_num >= col + mat.col_num)
    {
        switch(op)
        {
        case '+' :
            for(int i = 0; i < mat.row_num; ++i)
            {
                for(int j = 0; j < mat.col_num; ++j)
                {
                    mat_result.at(row + i, col + j) += mat.at(i, j);
                }
            }
            break;
        case '-' :
            for(int i = 0; i < mat.row_num; ++i)
            {
                for(int j = 0; j < mat.col_num; ++j)
                {
                    mat_result.at(row + i, col + j) -= mat.at(i, j);
                }
            }
            break;
        case '*' :
            for(int i = 0; i < mat.row_num; ++i)
            {
                for(int j = 0; j < mat.col_num; ++j)
                {
                    mat_result.at(row + i, col + j) *= mat.at(i, j);
                }
            }
            break;
        case '/' :
            for(int i = 0; i < mat.row_num; ++i)
            {
                for(int j = 0; j < mat.col_num; ++j)
                {
                    mat_result.at(row + i, col + j) /= mat.at(i, j);
                }
            }
            break;
        }
    }
    return mat_result;
}
template<typename T>
matrix<T> matrix<T>::get_local(size_t row, size_t col, size_t row_num, size_t col_num)
{
    matrix<T> mat_result(row_num, col_num);
    if(this->row_num >= row + row_num && this->col_num >= col + col_num)
    {
        for(int i = 0; i < row_num; ++i)
        {
            for(int j = 0; j < col_num; ++j)
            {
                mat_result.at(i, j) = this->at(row + i, col + j);
            }
        }
    }
    return mat_result;
}
template<typename T>
T* matrix<T>::get_data() const
{
    return this->data;
}
template<typename T>
bool matrix<T>::lu(matrix<T>& L, matrix<T>& U)
{
    // Doolittle algorithm.
    if(this->row_num != this->col_num)
    {
        return false;
    }
    size_t square_size = this->row_num;
    U = matrix<T>::zero(square_size, square_size);
    L = matrix<T>::eye(square_size);
    for(int i = 0; i < square_size; ++i)    // U(0, i)
    {
        U.at(0, i) = this->at(0, i);
    }
    if(U.at(0, 0) == (T)0)
    {
        return false;
    }
    for(int i = 1; i < square_size; ++i)    // L(i, 0)
    {
        L.at(i, 0) = this->at(i, 0) / U.at(0, 0);
    }
    for(int i = 1; i < square_size; ++i)
    {
        for(int j = i; j < square_size; ++j)    // U(i, j)
        {
            T tmp_value = (T)0;
            for(int k = 0; k < i; ++k)
            {
                tmp_value += L.at(i, k) * U.at(k, j);
            }
            U.at(i, j) = this->at(i, j) - tmp_value;
        }
        if(U.at(i, i) == 0)
        {
            return false;
        }
        for(int j = i+1; j < square_size; ++j)  // L(j, i)
        {
            if(i == (square_size - 1))
            {
                continue;
            }
            T tmp_value = (T)0;
            for(int k = 0; k < i; ++k)
            {
                tmp_value += L.at(j, k) * U.at(k, i);
            }
            L.at(j, i) = (this->at(j, i) - tmp_value) / U.at(i, i);
        }
    }
    return true;
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

}

#endif // MATRIX_HPP_INCLUDED
