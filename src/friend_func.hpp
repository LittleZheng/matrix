
/*
 *  friend_func.hpp
 *  zhengshaoyin
 *  2015/05/14
 *
 */

#ifndef FRIEND_FUNC_HPP_INCLUDED
#define FRIEND_FUNC_HPP_INCLUDED

namespace matrix_space
{
/**************************************************************/

template<typename T>
class matrix;

template<typename T>
std::ostream& operator<<(std::ostream& outs, const matrix<T>& mat);
template<typename T>
std::istream& operator>>(std::istream& ins, matrix<T>& mat);

template<typename T>
matrix<T> operator+(const matrix<T>& mat1, const matrix<T>& mat2);
template<typename T>
matrix<T> operator-(const matrix<T>& mat1, const matrix<T>& mat2);
template<typename T>
matrix<T> operator*(const matrix<T>& mat1, const matrix<T>& mat2);

template<typename T>
matrix<T> operator+(const T& value, const matrix<T>& mat2);
template<typename T>
matrix<T> operator-(const T& value, const matrix<T>& mat2);
template<typename T>
matrix<T> operator*(const T& value, const matrix<T>& mat2);

template<typename T>
matrix<T> operator+(const matrix<T>& mat1, const T& value);
template<typename T>
matrix<T> operator-(const matrix<T>& mat1, const T& value);
template<typename T>
matrix<T> operator*(const matrix<T>& mat1, const T& value);

/**************************************************************/

template<typename T>
std::ostream& operator<<(std::ostream& outs, const matrix<T>& mat)
{
    for(int i = 0; i < mat.get_row_num(); ++i)
    {
        for(int j = 0; j < mat.get_col_num(); ++j)
        {
            outs << mat.at(i, j) << " ";     // 1-D to 2-D
        }
        outs << std::endl;
    }
    return outs;
}
template<typename T>
std::istream& operator>>(std::istream& ins, matrix<T>& mat)
{
    for(int i = 0; i < mat.get_row_num(); ++i)
    {
        for(int j = 0; j < mat.get_col_num(); ++j)
        {
            ins >> mat.at(i, j);
        }
    }
    return ins;
}

template<typename T>
matrix<T> operator+(const matrix<T>& mat1, const matrix<T>& mat2)
{
    matrix<T> mat(mat1);
    if(mat1.get_row_num() == mat2.get_row_num() && mat1.get_col_num() == mat2.get_col_num())
    {
        mat += mat2;
    }
    return mat;
}
template<typename T>
matrix<T> operator-(const matrix<T>& mat1, const matrix<T>& mat2)
{
    matrix<T> mat(mat1);
    if(mat1.get_row_num() == mat2.get_row_num() && mat1.get_col_num() == mat2.get_col_num())
    {
        mat -= mat2;
    }
    return mat;
}
template<typename T>
matrix<T> operator*(const matrix<T>& mat1, const matrix<T>& mat2)
{
    matrix<T> mat(mat1);
    if(mat1.get_col_num() == mat2.get_row_num())
    {
        mat *= mat2;
    }

    return mat;
}

template<typename T>
matrix<T> operator+(const T& value, const matrix<T>& mat2)
{
    matrix<T> mat(mat2);
    mat += value;
    return mat;
}
template<typename T>
matrix<T> operator-(const T& value, const matrix<T>& mat2)
{
    matrix<T> mat(mat2);
    mat -= value;
    return mat;
}
template<typename T>
matrix<T> operator*(const T& value, const matrix<T>& mat2)
{
    matrix<T> mat(mat2);
    mat *= value;
    return mat;
}

template<typename T>
matrix<T> operator+(const matrix<T>& mat1, const T& value)
{
    matrix<T> mat(mat1);
    mat += value;
    return mat;
}
template<typename T>
matrix<T> operator-(const matrix<T>& mat1, const T& value)
{
    matrix<T> mat(mat1);
    mat -= value;
    return mat;
}
template<typename T>
matrix<T> operator*(const matrix<T>& mat1, const T& value)
{
    matrix<T> mat(mat1);
    mat *= value;
    return mat;
}

/**************************************************************/
}

#endif // FRIEND_FUNC_HPP_INCLUDED
