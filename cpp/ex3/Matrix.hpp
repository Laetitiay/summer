#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP
#define EXCEPTION_INVALID_ARGS "Invalid arguments"
#define EXCEPTION_OUT_OF_MATRIX "Out of matrix range"
#define MATRIX_DELIMETER '\t'


#include <vector>
#include <ostream>
#include <iostream>
#include <thread>
#include <future>
#include "Complex.h"

using std::vector;
using std::size_t;


/**
 * A class that represents a matrix of type T.
 */
template<class T>
class Matrix
{
private:
    size_t _rows;
    size_t _cols;
    vector<T> _matrix;
    static bool _parallel;

    Matrix<T> _parallelPlusOperator(const Matrix<T> &rhs) const;

    Matrix<T> _nonParallelPlusOperator(const Matrix<T> &rhs) const;

public:
    typedef typename vector<T>::const_iterator const_iterator;

    /**
     * default cntr
     * @return a 1x1 matrix with value T{0}
     */
    Matrix();

    /**
     * cntr for size matrix with 0 values
     * @param rows number of rows
     * @param cols number of columns
     * @return rows * cols matrix with 0 values
     */
    Matrix(size_t rows, size_t cols);

    /**
     * Copy constructor
     * @param other other matrix
     * @return copy of the matrix
     */
    Matrix(const Matrix<T> &other);

    /**
     * move constructor
     * @param other other matrix
     * @return moved matrix
     */
    Matrix(Matrix<T> && other);

    /**
     * Special constructor for specific values
     * @param rows number of rows
     * @param cols number of columns
     * @param cells vector of values to have in the matrix
     * @return new matrix with the values
     */
    Matrix(size_t rows, size_t cols, const vector<T> &cells);

    /**
     * Default destructor
     */
    ~Matrix() = default;

    /**
     * = operator.
     * @param rhs right hand side argument
     * @return the matrix
     */
    Matrix<T> operator=(const Matrix<T> &rhs);

    /**
     * Plus operator
     * @param rhs right hand side
     * @return matrix with values added by both
     */
    Matrix<T> operator+(const Matrix<T> &rhs) const;

    /**
     * Minus operator
     * @param rhs right hand side
     * @return  A new matrix with values of the first matrix minus the values of the second matrix
     */
    Matrix<T> operator-(const Matrix<T> &rhs) const;

    /**
     * Multipication operator
     * @param rhs right hand side
     * @return a matrix of multiplied two matricies
     */
    Matrix<T> operator*(const Matrix<T> &rhs) const;

    /**
     * Checks if the matricies are equal
     * @param rhs  other matrix
     * @return true iff they are equal in size and values
     */
    bool operator==(const Matrix<T> &rhs) const;

    /**
     * Not equal operator
     * @param rhs other matrix
     * @return true iff they are not the same size or have different values
     */
    bool operator!=(const Matrix<T> &rhs) const;

    /**
     * creates a transposed matrix
     * @return a transposed version of this
     */
    Matrix<T> trans() const;

    /**
     * Checks if the matrix is a square
     * @return true iff the number of rows equals to the number of columns
     */
    bool isSquareMatrix() const;

    /**
     * Prints the matrix to ostream
     * @param os ostream to output to
     * @param matrix matrix to print
     * @return the ostream
     */
    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix);

    /**
     * returns the element at the (row,column) cell of the matrix
     * @param row row
     * @param col column
     * @return the value at the (row,column) cell of the matrix
     */
    T &operator()(const size_t row, const size_t col)
    {
        if (row >= _rows || col >= _cols)
        {
            throw std::out_of_range(EXCEPTION_OUT_OF_MATRIX);
        }
        return _matrix[row * _cols + col];
    }

    /**
     * returns the value at the (row,column) cell of the matrix
     * @param row row
     * @param col column
     * @return returns the value at the (row,column) cell of the matrix
     */
    T const &operator()(const size_t row, const size_t col) const
    {
        if (row >= _rows || col >= _cols)
        {
            throw std::out_of_range(EXCEPTION_OUT_OF_MATRIX);
        }
        return _matrix[row * _cols + col];
    }

    /**
     * Begin iterator of the matrix
     * @return begin
     */
    const_iterator begin() const
    {
        return _matrix.cbegin();
    }

    /**
     * End iterator of the matrix
     * @return end
     */
    const_iterator end() const
    {
        return _matrix.cend();
    }

    /**
     * rows in the matrix
     * @return number of rows in the matrix
     */
    size_t rows() const;

    /**
     * Columns in the matrix
     * @return number of columns in the matrix
     */
    size_t cols() const;

    /**
     * Sets the class to parallel calculations if true, opposite if false.
     */
    static void setParallel(bool);



};

template<typename T>
bool Matrix<T>::_parallel = false;

template<typename T>
Matrix<T>::Matrix() : _rows{1}, _cols{1}, _matrix{T{0}}
{}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows{rows}, _cols{cols}, _matrix(rows * cols)
{
    if (rows == 0 || cols == 0)
    {
        throw std::invalid_argument(EXCEPTION_INVALID_ARGS);
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const vector<T> &cells) : _rows{rows}, _cols{cols}, _matrix{cells}
{
    if (cells.size() != rows * cols)
    {
        throw std::invalid_argument(EXCEPTION_INVALID_ARGS);
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other) : _rows{other._rows}, _cols{other._cols}, _matrix{other._matrix}
{}


template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) : _rows{other._rows}, _cols{other._cols}, _matrix{std::move(other._matrix)}
{}

template<typename T>
bool Matrix<T>::isSquareMatrix() const
{
    return _rows == _cols;
}

template<typename T>
size_t Matrix<T>::cols() const
{
    return _cols;
}

template<typename T>
size_t Matrix<T>::rows() const
{
    return _rows;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix &rhs) const
{
    return (_rows == rhs._rows && _cols == rhs._cols) && _matrix == rhs._matrix;
}

template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &rhs)
{
    if (*this == rhs)
    {
        return *this;
    }
    _matrix = rhs._matrix;
    _rows = rhs._rows;
    _cols = rhs._cols;
    return *this;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix &rhs) const
{
    return !(operator==(rhs));
}

template<typename T>
void Matrix<T>::setParallel(bool val)
{
    if (val == _parallel)
    {
        return;
    }
    _parallel = val;
    std::cout << "Generic Matrix mode changed to " << (val ? "" : "non-") << "parallel mode." << std::endl;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) const
{
    if (_parallel)
    {
        return _parallelPlusOperator(rhs);
    }
    return _nonParallelPlusOperator(rhs);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &rhs) const
{
    if (_cols != rhs._rows)
    {
        throw std::invalid_argument(EXCEPTION_INVALID_ARGS);
    }

    Matrix<T> ret(_rows, rhs._cols);
    auto multiplyRow = [&ret, this, &rhs](size_t i)
    {
        for (size_t j = 0; j < rhs._cols; ++j)
        {
            T sum{0};
            for (size_t k = 0; k < _cols; ++k)
            {
                sum += ((*this)(i, k) * rhs(k, j));
            }
            ret(i, j) = sum;
        }
    };

    vector<std::future<void>> results;
    for (size_t i = 0; i < _rows; ++i)
    {
        _parallel ? results.push_back(std::async(multiplyRow, i)) : multiplyRow(i);
    }

    if (_parallel)
    {
        for (const auto &res: results)
        {
            res.wait();
        }
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::_nonParallelPlusOperator(const Matrix &rhs) const
{
    if (_cols != rhs._cols || _rows != rhs._rows)
    {
        throw std::invalid_argument(EXCEPTION_INVALID_ARGS);
    }
    Matrix ret{*this};
    for (size_t k = 0; k < _cols * _rows; ++k)
    {
        ret._matrix[k] += rhs._matrix[k];
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::_parallelPlusOperator(const Matrix<T> &rhs) const
{
    if (_cols != rhs._cols || _rows != rhs._rows)
    {
        throw std::invalid_argument(EXCEPTION_INVALID_ARGS);
    }
    Matrix ret(*this);
    auto sumRow = [&ret, &rhs](size_t i)
    {
        for (size_t j = 0; j < ret.cols(); ++j)
        {
            ret(i, j) += rhs(i, j);
        }
    };
    vector<std::future<void>> results;
    for (size_t i = 0; i < _rows; ++i)
    {
        results.push_back(
                std::async(
                        sumRow, i
                )
        );
    }
    for (const auto &res: results)
    {
        res.wait();
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &rhs) const
{
    if (_cols != rhs._cols || _rows != rhs._rows)
    {
        throw std::invalid_argument(EXCEPTION_INVALID_ARGS);
    }
    Matrix ret{*this};
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            ret(i, j) -= rhs(i, j);
        }
    }
    return ret;
}

template<>
inline Matrix<Complex> Matrix<Complex>::trans() const
{
    Matrix<Complex> transposed(_cols, _rows);
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            transposed(j, i) = (*this)(i, j).conj();
        }
    }
    return transposed;
}


template<typename T>
Matrix<T> Matrix<T>::trans() const
{
    Matrix<T> transposed{_cols, _rows};
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            transposed(j, i) = (*this)(i, j);
        }
    }
    return transposed;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    for (size_t i = 0; i < matrix._rows; ++i)
    {
        for (size_t j = 0; j < matrix._cols; ++j)
        {
            os << matrix(i, j) << MATRIX_DELIMETER;
        }
        os << std::endl;
    }
    return os;
}

#endif
