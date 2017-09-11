//
// Created by liron on 9/11/17.
//

#ifndef EX3_MATRIX_HPP
#define EX3_MATRIX_HPP


#include <vector>
#include <ostream>
#include <iostream>

template <class T>
class Matrix
{
public:
    Matrix();
    Matrix(std::size_t rows, std::size_t cols);
    Matrix(const Matrix<T> &other);
    Matrix(Matrix<T>&& other);
    Matrix(std::size_t rows, std::size_t cols, const std::vector<T>& cells);
    ~Matrix() = default;
    Matrix<T> operator=(const Matrix<T> &rhs);
    Matrix<T> operator+(const Matrix<T> &rhs);
    Matrix<T> operator-(const Matrix<T> &rhs);
    Matrix<T> operator*(const Matrix<T> &rhs);
    bool operator==(const Matrix<T> &rhs)const;
    bool operator!=(const Matrix<T> &rhs)const;
    Matrix<T> trans()const;
    bool isSquareMatrix()const;
    std::ostream& operator<<(std::ostream& os, const Matrix<T> &rhs)const;
    <T> operator()(std::size_t row, std::size_t col);
    <T> operator()(std::size_t row, std::size_t col)const; // todo: is that what they mean by const?
    std::bidirectional_iterator_tag begin(); // TODO: which type?
    std::bidirectional_iterator_tag end(); // TODO: which type?
    size_t rows()const;
    size_t cols()const;
    static void setParallel(bool);


private:
    std::vector<T> _matrix;
    std::size_t _rows;
    std::size_t _cols;
    static bool _parallel;

    Matrix<T> ParallelPlusOperator(const Matrix<T> &rhs);
    Matrix<T> NonParallelPlusOperator(const Matrix<T> &rhs);
    Matrix<T> ParallelMultiplyOperator(const Matrix<T> &rhs);
    Matrix<T> NonParallelMultiplyOperator(const Matrix<T> &rhs);

};

template <typename T>
Matrix<T>::Matrix() : _matrix{0} , _rows{1}, _cols{1} {}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols) : _rows{rows}, _cols{cols}, _matrix(rows * cols) {}

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const std::vector<T> &cells) : _matrix(rows * cols), _rows{rows}, _cols{cols}
{

}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other) : _rows{other._rows}, _cols{other._cols}, _matrix{other._matrix} {}  //TODO: Is that the default?


template <typename T>
Matrix<T>::Matrix(Matrix<T> &&other) {}

template <typename T>
bool Matrix<T>::isSquareMatrix() const
{
    return _rows == _cols;
}

template <typename T>
size_t Matrix<T>::cols() const
{
    return _cols;
}

template <typename T>
size_t Matrix<T>::rows() const
{
    return _rows;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix &rhs) const
{
    if (_rows != rhs._rows || _cols != rhs._cols)
    {
        return false;
    }
    for (int i = 0; i < _rows * _cols; ++i)
    {
        if (_matrix[i] != rhs._matrix[i])
        {
            return false;
        }
    }
    return true;
}


template <typename T>
bool Matrix<T>::operator!=(const Matrix &rhs) const
{
    return !(operator==(rhs));
}

template <typename T>
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

template <typename T>
Matrix<T> Matrix::operator+(const Matrix &rhs)
{
    if (_parallel)
    {
        return ParallelPlusOperator(rhs);
    }
    return NonParallelPlusOperator(rhs);
}

template <typename T>
Matrix<T> Matrix::operator*(const Matrix &rhs)
{
    if (_parallel)
    {
        return ParallelMultiplyOperator(rhs);
    }
    return NonParallelMultiplyOperator(rhs);
}

#endif //EX3_MATRIX_HPP

int main()
{
    Matrix<int> a{};
}