#pragma once

#include <cstddef>
#include <iterator>
#include <iostream>

template <class T>
class ColIterator : public std::iterator<std::random_access_iterator_tag, T> {
    
    private:
    T* p;
    size_t cols;

public:

    ColIterator() : p(nullptr), cols(0) {

    }

    ColIterator(T* p, size_t cols) : p(p), cols(cols) {

    }
    ColIterator(const ColIterator &it) : p(it.p), cols(it.cols) {

    }
    ColIterator& operator=(const ColIterator& other) {
      p = other.p;
      cols = other.cols;
      return *this;
    }
    
    bool operator!=(ColIterator const& other) const {
      return p != other.p;
    }
    bool operator==(ColIterator const& other) const {
      return p == other.p;
    }
    

    T& operator*() const {
      return *p;
    }
    ColIterator& operator++() {
      p += cols;
      return *this;
    }
    ColIterator operator++ (int)
    {
        ColIterator copy {*this};
        ++(*this);
        return copy;
    }
    ColIterator& operator-- ()
    {
        p -= cols;
        return *this;
    }
    ColIterator operator-- (int)
    {
        ColIterator copy {*this};
        --(*this);
        return copy;
    }


    friend ColIterator operator+(const ColIterator& it, const size_t& x) {
      return ColIterator(it.p + x * it.cols, it.cols);
    }
    friend ColIterator operator+(const ColIterator& it, const std::ptrdiff_t& x) {
      return ColIterator(it.p + x * it.cols, it.cols);
    }
    friend ColIterator operator+(const std::ptrdiff_t& x, const ColIterator& it) {
      return ColIterator(it.p + x * it.cols, it.cols);
    }
    
    friend ColIterator operator-(const ColIterator& it, const size_t& x) {
      return ColIterator(it.p - x * it.cols, it.cols);
    }
    friend ColIterator operator-(const ColIterator& it, const std::ptrdiff_t& x) {
      return ColIterator(it.p - x * it.cols, it.cols);
    }
    friend ColIterator operator-(const std::ptrdiff_t& x, const ColIterator& it) {
      return ColIterator(it.p - x * it.cols, it.cols);
    }
    friend int64_t operator-(const ColIterator& it1, const ColIterator& it2) {
      return (it1.p - it2.p) / (int64_t)it1.cols;
    }
    
    
    template <typename T2>
    ColIterator& operator+=(T2 number)
    {
        p += (number * cols);
        return *this;
    }

    template <typename T2>
    ColIterator& operator-=(T2 number)
    {
        p -= (number * cols);
        return *this;
    }

    friend bool operator<(const ColIterator& it1, const ColIterator& it2) {
      return it1.p < it2.p;
    }

    friend bool operator>(const ColIterator& it1, const ColIterator& it2) {
      return it1.p > it2.p;
    }

    friend bool operator<=(const ColIterator& it1, const ColIterator& it2) {
      return it1.p <= it2.p;
    }

    friend bool operator>=(const ColIterator& it1, const ColIterator& it2) {
      return it1.p >= it2.p;
    }
    
    
    T& operator[](size_t idx) {
      ColIterator it = (*this) + idx;
      return *it.p;
    }
    
    T* operator->() const {
      return p;
    }
};



// Matrix

template <class T>
class matrix {
public:
  using value_type = T;

  using reference = T&;
  using const_reference = const T&;

  using pointer = T*;
  using const_pointer = const T*;

  using iterator = pointer;
  using const_iterator = const_pointer;

  using row_iterator = pointer;
  using const_row_iterator = const_pointer;

  using col_iterator = ColIterator<T>;
  using const_col_iterator = ColIterator<T>;

private:
  size_t _rows = 0, _cols = 0;
  T* _data = nullptr;

public:
  matrix();

  matrix(size_t rows, size_t cols);

  template <size_t Rows, size_t Cols>
  matrix(const T (&init)[Rows][Cols]);

  matrix(const matrix& other);

  matrix& operator=(const matrix& other);

  ~matrix();

  // Iterators

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  row_iterator row_begin(size_t row);
  const_row_iterator row_begin(size_t row) const;
  row_iterator row_end(size_t row);
  const_row_iterator row_end(size_t row) const;

  col_iterator col_begin(size_t col);
  const_col_iterator col_begin(size_t col) const;
  col_iterator col_end(size_t col);
  const_col_iterator col_end(size_t col) const;

  // Size

  size_t rows() const {
    return _rows;
  }
  size_t cols() const {
    return _cols;
  }
  size_t size() const {
    return _rows * _cols;
  }
  bool empty() const {
    return _rows == 0 || _cols == 0;
  }

  // Elements access

  reference operator()(size_t row, size_t col) {
    return *(_data + row * _cols + col);
  }
  const_reference operator()(size_t row, size_t col) const {
    return *(_data + row * _cols + col);
  }

  pointer data() {
    return _data;
  }
  const_pointer data() const {
    return _data;
  }

  // Comparison

  friend bool operator==(const matrix& left, const matrix& right) {
    if (left.rows() != right.rows() || left.cols() != right.cols())
    {
      return false;
    }
    
    for (size_t i = 0; i < left.size(); i++)
    {
      if (left._data[i] != right._data[i])
      {
        return false;
      }
    }
    return true;
  }

  friend bool operator!=(const matrix& left, const matrix& right) {
    if (left.rows() != right.rows() || left.cols() != right.cols())
    {
      return true;
    }

    for (size_t i = 0; i < left.size(); i++)
    {
      if (left._data[i] != right._data[i])
      {
        return true;
      }
    }
    return false;
  }

  // Arithmetic operations

  matrix& operator+=(const matrix& other) {
    for (size_t i = 0; i < other.rows(); i++)
    {
      for (size_t j = 0; j < other.cols(); j++) {
        (*this)(i, j) += other(i, j);
      }
    }
    return *this;
  }
  matrix& operator-=(const matrix& other) {
    for (size_t i = 0; i < other.rows(); i++)
    {
      for (size_t j = 0; j < other.cols(); j++) {
        (*this)(i, j) -= other(i, j);
      }
    }
    return *this;
  }
  matrix& operator*=(const matrix& other) {
    matrix m(other);

    for (size_t i = 0; i < m.rows(); i++)
    {
      for (size_t j = 0; j < m.cols(); j++) {
        T sum = 0;
        for (size_t k = 0; k < cols(); k++)
        {
          sum += operator()(i, k) * other(k, j);
        }
        m(i, j) = sum;
      }
    }

    delete[] _data;
    _data = m._data;
    _rows = m._rows;
    _cols = m._cols;
    m._data = nullptr;

    return *this;
  }
  matrix& operator*=(const_reference factor) {
    for (size_t i = 0; i < rows(); i++)
    {
      for (size_t j = 0; j < cols(); j++) {
        operator()(i, j) *= factor;
      }
    }
    return *this;
  }

  friend matrix operator+(const matrix& left, const matrix& right) {
    matrix m(left);
    for (size_t i = 0; i < left.rows(); i++)
    {
      for (size_t j = 0; j < left.cols(); j++) {
        m(i, j) = left(i, j) + right(i, j);
      }
    }
    return m;
  }
  friend matrix operator-(const matrix& left, const matrix& right) {
    matrix m(left);
    for (size_t i = 0; i < left.rows(); i++)
    {
      for (size_t j = 0; j < left.cols(); j++) {
        m(i, j) = left(i, j) - right(i, j);
      }
    }
    return m;
  }
  friend matrix operator*(const matrix& left, const matrix& right) {
    matrix m(right);
    for (size_t i = 0; i < m.rows(); i++)
    {
      for (size_t j = 0; j < m.cols(); j++) {
        T sum = 0;
        for (size_t k = 0; k < left.cols(); k++)
        {
          sum += left(i, k) * right(k, j);
        }
        m(i, j) = sum;
      }
    }
    return m;
  }
  friend matrix operator*(const matrix& left, const_reference right) {
    matrix m(left.rows(), left.cols());
    for (size_t i = 0; i < m.rows(); i++)
    {
      for (size_t j = 0; j < m.cols(); j++) {
        m(i, j) = left(i, j) * right;
      }
    }
    return m;
  }
  friend matrix operator*(const_reference left, const matrix& right) {
    return right * left;
  }

  
};

template <class T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& m) {
  for (size_t i = 0; i < m.rows(); i++)
  {
    for (size_t j = 0; j < m.cols(); j++) {
      out << m(i, j) << "  ";
    }
    out << std::endl;
  }
}

template <class T>
matrix<T>::matrix() : _rows(0), _cols(0), _data(nullptr) {

}

template <class T>
matrix<T>::matrix(size_t rows, size_t cols) 
  : 
  _rows(rows > 0 && cols > 0 ? rows : 0), 
  _cols(rows > 0 && cols > 0 ? cols : 0), 
  _data((rows > 0 && cols > 0) ? (new T[rows * cols]) : nullptr) {

  }

template <class T>
template <size_t Rows, size_t Cols>
matrix<T>::matrix(const T (&init)[Rows][Cols]) : matrix(Rows, Cols) {
  for (size_t i = 0; i < Rows; i++)
  {
    for (size_t j = 0; j < Cols; j++)
    {
      operator()(i, j) = init[i][j];
    }
  }
}

template <class T>
matrix<T>::matrix(const matrix& other) : matrix(other._rows, other._cols) {
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _cols; j++)
    {
      operator()(i, j) = other(i, j);
    }
  }
}

template <class T>
matrix<T>& matrix<T>::operator=(const matrix& other) {
  if (*this == other) {
    return *this;
  }
  
  if (_data != nullptr)
  {
    delete[] _data;
  }

  _data = nullptr;
  _rows = other.rows();
  _cols = other.cols();

  if (!other.empty())
  {
    _data = new T[other.rows() * other.cols()];

    for (size_t i = 0; i < other.rows(); i++)
    {
      for (size_t j = 0; j < other.cols(); j++)
      {
        operator()(i, j) = other(i, j);
      }
    }
  }

  return *this;
}

template <class T>
matrix<T>::~matrix() {
  if (_data != nullptr)
  {
    delete[] _data;
  }
  
}

// Iterator

template <class T>
matrix<T>::iterator matrix<T>::begin() {
  return _data;
}

template <class T>
matrix<T>::const_iterator matrix<T>::begin() const {
  return _data;
}

template <class T>
matrix<T>::iterator matrix<T>::end() {
  return _data + _rows * _cols;
}

template <class T>
matrix<T>::const_iterator matrix<T>::end() const {
  return _data + _rows * _cols;
}

// Rows iter
template <class T>
matrix<T>::row_iterator matrix<T>::row_begin(size_t row) {
  return _data + row * _cols;
}

template <class T>
matrix<T>::const_row_iterator matrix<T>::row_begin(size_t row) const {
  return _data + row * _cols;
}

template <class T>
matrix<T>::row_iterator matrix<T>::row_end(size_t row) {
  return _data + row * _cols + _cols;
}

template <class T>
matrix<T>::const_row_iterator matrix<T>::row_end(size_t row) const {
  return _data + row * _cols + _cols;
}


// Cols iter
template <class T>
matrix<T>::col_iterator matrix<T>::col_begin(size_t col) {
  ColIterator it(_data + col, _cols);
  return it;
}

template <class T>
matrix<T>::const_col_iterator matrix<T>::col_begin(size_t col) const {
  ColIterator it(_data + col, _cols);
  return it;
}

template <class T>
matrix<T>::col_iterator matrix<T>::col_end(size_t col) {
  ColIterator it(_data + col + _cols * _rows, _cols);
  return it;
}

template <class T>
matrix<T>::const_col_iterator matrix<T>::col_end(size_t col) const {
  ColIterator it(_data + col + _cols * _rows, _cols);
  return it;
}
