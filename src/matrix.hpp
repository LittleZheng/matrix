
/*
 *  matrix.hpp
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

/******************************************************************************/

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
    T sum() const;    // All elements add up.
    T max(size_t& row, size_t& col) const;
    T max() const;
    T min(size_t& row, size_t& col) const;
    T min() const;
    matrix<T> transpose() const;
    matrix<T> rotate90() const;
    matrix<T> reciprocal() const;
    matrix<T> sin() const;
    matrix<T> cos() const;
    matrix<T> exp() const;
    matrix<T> sqrt() const;
    matrix<T> log() const;
    matrix<T> pow(const T& exponent) const;
    matrix<T> dot(char op, const matrix<T>& mat) const;
    matrix<T> local_dot(char op, const matrix<T>& mat, size_t row, size_t col) const; // The size of mat should be less than *this's.
    matrix<T> get_local(size_t row, size_t col, size_t row_num, size_t col_num) const;
    T* get_data() const;
    bool is_square() const;
    void row_swap(size_t row1, size_t row2);
    void col_swap(size_t col1, size_t col2);
    bool lu(matrix<T>& L, matrix<T>& U) const;    // Matrix(0, 0) can not be zero.
    bool lu(matrix<T>& P, matrix<T>& L, matrix<T>& U) const;
    T det() const;
    matrix<T> inverse() const;
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

/******************************************************************************/

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

/******************************************************************************/

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
T matrix<T>::sum() const
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
T matrix<T>::max(size_t& row, size_t& col) const
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
T matrix<T>::max() const
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
T matrix<T>::min(size_t& row, size_t& col) const
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
T matrix<T>::min() const
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
matrix<T> matrix<T>::transpose() const
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
matrix<T> matrix<T>::rotate90() const
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
matrix<T> matrix<T>::reciprocal() const
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
matrix<T> matrix<T>::sin() const
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
matrix<T> matrix<T>::cos() const
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
matrix<T> matrix<T>::exp() const
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
matrix<T> matrix<T>::sqrt() const
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
matrix<T> matrix<T>::log() const
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
matrix<T> matrix<T>::pow(const T& exponent) const
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
matrix<T> matrix<T>::dot(char op, const matrix<T>& mat) const
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
matrix<T> matrix<T>::local_dot(char op, const matrix<T>& mat, size_t row, size_t col) const
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
matrix<T> matrix<T>::get_local(size_t row, size_t col, size_t row_num, size_t col_num) const
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
bool matrix<T>::is_square() const
{
    return ((this->row_num == this->col_num));
}
template<typename T>
void matrix<T>::row_swap(size_t row1, size_t row2)
{
    for(int i = 0; i < this->col_num; ++i)
    {
        T tmp_value = this->at(row1, i);
        this->at(row1, i) = this->at(row2, i);
        this->at(row2, i) = tmp_value;
    }
}
template<typename T>
void matrix<T>::col_swap(size_t col1, size_t col2)
{
    for(int i = 0; i < this->row_num; ++i)
    {
        T tmp_value = this->at(i, col1);
        this->at(i, col1) = this->at(i, col2);
        this->at(i, col2) = tmp_value;
    }
}
template<typename T>
bool matrix<T>::lu(matrix<T>& L, matrix<T>& U) const
{
    // Doolittle algorithm.
    if(!(this->is_square()) || (this->at(0, 0) == (T)0))
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
template<typename T>
bool matrix<T>::lu(matrix<T>& P, matrix<T>& L, matrix<T>& U) const
{
    // Doolittle algorithm.
    if(!(this->is_square()))
    {
        return false;
    }

    matrix<T> tmp_mat(*this);
    size_t square_size = tmp_mat.row_num;
    P = matrix<T>::eye(square_size);
    if(tmp_mat.at(0, 0) == (T)0)
    {
        for(size_t i = 1; i < square_size; ++i)
        {
            if(tmp_mat.at(i, 0) != (T)0)
            {
                P.row_swap(0, i);
                tmp_mat.row_swap(0, i);
                break;
            }
        }
    }
    if(tmp_mat.at(0, 0) == (T)0)
    {
        return false;
    }
    return tmp_mat.lu(L, U);
}
template<typename T>
T matrix<T>::det() const
{
    T det_value = (T)0;
    if(!(this->is_square()))
    {
        return det_value;
    }

    matrix<T> tmp_mat(*this);
    size_t square_size = tmp_mat.row_num;
    bool is_change_sign = false;
    if(tmp_mat.at(0, 0) == (T)0)
    {
        for(size_t i = 1; i < square_size; ++i)
        {
            if(tmp_mat.at(i, 0) != (T)0)
            {
                is_change_sign = true;
                tmp_mat.row_swap(0, i);
                break;
            }
        }
    }
    if(tmp_mat.at(0, 0) == (T)0)
    {
        return det_value;
    }
    matrix<T> L;
    matrix<T> U;
    if(tmp_mat.lu(L, U))
    {
        det_value = (T)1;
        for(int i = 0; i < square_size; ++i)
        {
            det_value *= U.at(i, i);
        }
        if(is_change_sign)
        {
            det_value *= (T)-1;
        }
    }
    else
    {
        det_value = (T)0;
    }

    return det_value;
}
template<typename T>
matrix<T> matrix<T>::inverse() const    // Failed if the inverse matrix is all zero.
{
    size_t square_size = this->row_num;
    matrix<T> mat_result = matrix<T>::zero(square_size, square_size);
    if(!(this->is_square()))
    {
        return mat_result;
    }

    matrix<T> tmp_mat(*this);
    matrix<T> P_inverse = matrix<T>::eye(square_size);
    if(tmp_mat.at(0, 0) == (T)0)
    {
        for(size_t i = 1; i < square_size; ++i)
        {
            if(tmp_mat.at(i, 0) != (T)0)
            {
                P_inverse.col_swap(0, i);   // P^-1
                tmp_mat.row_swap(0, i);
                break;
            }
        }
    }
    if(tmp_mat.at(0, 0) == (T)0)
    {
        return mat_result;
    }
    matrix<T> L;
    matrix<T> U;
    if(!(tmp_mat.lu(L, U)))
    {
        return mat_result;
    }
    matrix<T> U_inverse = matrix<T>::zero(square_size, square_size);
    matrix<T> L_inverse = matrix<T>::zero(square_size, square_size);
    for(int i = 0; i < square_size; ++i)
    {
        U_inverse.at(i, i) = (T)1 / U.at(i, i);
        L_inverse.at(i, i) = (T)1 / L.at(i, i);
    }
    for(int i = 0; i < square_size; ++i)
    {
        for(int j = i+1; j < square_size; ++j)
        {
            T U_tmp_value = (T)0;
            T L_tmp_value = (T)0;
            for(int k = i; k < j; ++k)
            {
                U_tmp_value += U_inverse.at(i, k) * U.at(k, j);
                L_tmp_value += L.at(j, k) * L_inverse.at(k, i);

            }
            U_inverse.at(i, j) = -U_tmp_value / U.at(j, j);
            L_inverse.at(j, i) = -L_tmp_value / L.at(j, j);
        }
    }
    mat_result = U_inverse * L_inverse * P_inverse;
    return mat_result;
}

/******************************************************************************/

template<typename T>
void matrix<T>::operator+=(const matrix<T>& mat)
{
    if(this->row_num == mat.rows() && this->col_num == mat.cols())
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
    if(this->row_num == mat.rows() && this->col_num == mat.cols())
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

/******************************************************************************/

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

/******************************************************************************/

}

#endif // MATRIX_HPP_INCLUDED
