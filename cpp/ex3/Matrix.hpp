//
// Created by liron on 9/11/17.
//

#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP


#include <vector>
#include <ostream>
#include <iostream>
#include <thread>
#include <future>

using std::vector;
using std::size_t;


template<class T>
class Matrix
{
public:
    typedef typename vector<T>::const_iterator matrixIterator;

    Matrix();

    Matrix(size_t rows, size_t cols);

    Matrix(const Matrix<T> &other);

    Matrix(Matrix<T> &&other);

    Matrix(size_t rows, size_t cols, const vector<T> &cells);

    ~Matrix() = default;

    Matrix<T> operator=(const Matrix<T> &rhs);

    Matrix<T> operator+(const Matrix<T> &rhs) const;

    Matrix<T> operator-(const Matrix<T> &rhs) const;

    Matrix<T> operator*(const Matrix<T> &rhs) const;

    bool operator==(const Matrix<T> &rhs) const;

    bool operator!=(const Matrix<T> &rhs) const;

    Matrix<T> trans() const;

    bool isSquareMatrix() const;

    template<class U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix);

    T &operator()(size_t row, size_t col);

    const T &operator()(size_t row, size_t col) const; // todo: is that what they mean by const?
    matrixIterator begin() const // TODO: which type?
    {
        return _matrix.cbegin();
    }

    matrixIterator end() const
    {
        return _matrix.cend();
    }

    size_t rows() const;

    size_t cols() const;

    static void setParallel(bool);


private:
    vector<T> _matrix;
    size_t _rows;
    size_t _cols;
    static bool _parallel;

    Matrix<T> parallelPlusOperator(const Matrix<T> &rhs) const;

    Matrix<T> nonParallelPlusOperator(const Matrix<T> &rhs) const;

    Matrix<T> parallelMultiplyOperator(const Matrix<T> &rhs) const;

    Matrix<T> nonParallelMultiplyOperator(const Matrix<T> &rhs) const;

};

template<typename T>
bool Matrix<T>::_parallel = false;

template<typename T>
Matrix<T>::Matrix() : _matrix{T{0}}, _rows{1}, _cols{1}
{}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : _rows{rows}, _cols{cols}, _matrix(rows * cols)
{
    //TODO: Is it needed?
    for (size_t i = 0; i < rows * cols; ++i)
    {
        _matrix[i] = T{0};
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols, const vector<T> &cells) : _matrix{cells}, _rows{rows}, _cols{cols}
{
    if (cells.size() != rows * cols)
    {
        // TODO: better exception
        throw;
    }
}

/**
 * Copy cntr
 * @param other
 * @return
 */
template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other) : _rows{other._rows}, _cols{other._cols}, _matrix{other._matrix}
{}


template<typename T>
Matrix<T>::Matrix(Matrix<T> &&other) : _matrix{std::move(other._matrix)}, _rows{other._rows}, _cols{other._cols}
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
    std::cout << "Generic Matrix mode changed to " << (val ? "parallel" : "non-parallel") << " mode.\n";
    // TODO: define
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) const
{
    if (_parallel)
    {
        return parallelPlusOperator(rhs);
    }
    return nonParallelPlusOperator(rhs);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &rhs) const
{
    if (_parallel)
    {
        return parallelMultiplyOperator(rhs);
    }
    return nonParallelMultiplyOperator(rhs);
}

template<typename T>
T &Matrix<T>::operator()(const size_t row, const  size_t col)
{
    if (row > _rows || col > _cols)
    {
        throw std::out_of_range("Out of matrix range");
    }
    return _matrix[row * _cols + col];
}

template<typename T>
const T &Matrix<T>::operator()(size_t row, size_t col) const
{
    if (row > _rows || col > _cols)
    {
        throw std::out_of_range("Out of matrix range");
    }
    return _matrix[row * _cols + col];
}

template<typename T>
Matrix<T> Matrix<T>::nonParallelPlusOperator(const Matrix &rhs) const
{
    if (_cols != rhs._cols || _rows != rhs._rows)
    {
        throw;
        // TODO: make exception
    }
    Matrix ret{*this};
    for (int k = 0; k < _cols * _rows; ++k)
    {
        ret._matrix[k] += rhs._matrix[k];
    }
//    for (size_t i = 0; i < _rows; ++i)
//    {
//        for (size_t j = 0; j < _cols; ++j)
//        {
//            ret(i,j) += rhs(i,j);
//        }
//    }
    return ret;
}


template<typename T>
Matrix<T> Matrix<T>::nonParallelMultiplyOperator(const Matrix<T> &rhs) const
{
    if (_cols != rhs._rows)
    {
        throw;
        //TODO: create exception
    }

    Matrix<T> ret(_rows, rhs._cols);
    for (size_t i = 0; i < _rows; ++i)
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

    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::parallelPlusOperator(const Matrix<T> &rhs) const
{
    if (_cols != rhs._cols || _rows != rhs._rows)
    {
        throw;
        // TODO: make exception
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
Matrix<T> Matrix<T>::parallelMultiplyOperator(const Matrix<T> &rhs) const
{
    if (_cols != rhs._rows)
    {
        throw;
        //TODO: create exception
    }

    Matrix<T> ret(_rows, rhs._cols);
    auto sumRow = [&ret, this, &rhs](size_t i)
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
        throw;
        // TODO: make exception
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

template<typename T>
Matrix<T> Matrix<T>::trans() const
{
    Matrix<T> ret{_cols, _rows};
    for (size_t i = 0; i < _rows; ++i)
    {
        for (size_t j = 0; j < _cols; ++j)
        {
            ret(j, i) = (*this)(i, j);
        }
    }
    return ret;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    for (size_t i = 0; i < matrix._rows; ++i)
    {
        for (size_t j = 0; j < matrix._cols; ++j)
        {
            os << matrix(i, j) << '\t';
        }
        os << std::endl;
    }
    return os;
}


#endif //EX3_MATRIX_HPP
//
//int main()
//{
//    vector<int> a{1,2,3,4,5,6,7,8,9,10,11,12};
//    vector<int> b{6,-2,3,7,1,9,4,9,4};
//    vector<int> d{1,2,3,4};
//    Matrix<int> c{3,4,a};
//    Matrix<int> e{2,2,d};
//    Matrix<int>::setParallel(true);
//    std::cout << (e*e) << std::endl;
//
//}