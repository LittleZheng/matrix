
/*
 *  base_matrix.hpp
 *  zhengshaoyin
 *  2015/05/14
 *
 */

#ifndef BASE_MATRIX_HPP_INCLUDED
#define BASE_MATRIX_HPP_INCLUDED

namespace matrix_space
{
/**************************************************************/

template<typename T>
class base_matrix
{
public :
    base_matrix();
    base_matrix(size_t row_num, size_t col_num);
    base_matrix(const base_matrix<T>& mat);
    ~base_matrix();
public :
    size_t get_row_num() const;
    size_t get_col_num() const;
    T at(size_t row, size_t col) const;
    T& at(size_t row, size_t col);
protected :
    size_t row_num;
    size_t col_num;
    T* data;
};

/**************************************************************/

template<typename T>
base_matrix<T>::base_matrix()
{
    this->data = NULL;
    this->row_num = 256;
    this->col_num = 1;
    this->data = new T[this->row_num * this->col_num];
}
template<typename T>
base_matrix<T>::base_matrix(size_t row_num, size_t col_num)
{
    this->data = NULL;
    this->row_num = row_num;
    this->col_num = col_num;
    this->data = new T[this->row_num * this->col_num];
}
template<typename T>
base_matrix<T>::~base_matrix()
{
    if(NULL != this->data)
    {
        delete [] this->data;
        this->data = NULL;
    }
}

/**************************************************************/

template<typename T>
size_t base_matrix<T>::get_row_num() const
{
    return this->row_num;
}
template<typename T>
size_t base_matrix<T>::get_col_num() const
{
    return this->col_num;
}
template<typename T>
T base_matrix<T>::at(size_t row, size_t col) const
{
    return this->data[row * this->col_num + col];
}
template<typename T>
T& base_matrix<T>::at(size_t row, size_t col)
{
    return this->data[row * this->col_num + col];
}

/**************************************************************/
}

#endif // BASE_MATRIX_HPP_INCLUDED
