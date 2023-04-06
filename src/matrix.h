#pragma once

#include <cstddef>

template <class T>
class matrix {
public:
  using value_type = T;

  using reference = T&;
  using const_reference = const T&;

  using pointer = T*;
  using const_pointer = const T*;

  using iterator = void;
  using const_iterator = void;

  using row_iterator = void;
  using const_row_iterator = void;

  using col_iterator = void;
  using const_col_iterator = void;

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

  size_t rows() const;
  size_t cols() const;
  size_t size() const;
  bool empty() const;

  // Elements access

  reference operator()(size_t row, size_t col);
  const_reference operator()(size_t row, size_t col) const;

  pointer data();
  const_pointer data() const;

  // Comparison

  friend bool operator==(const matrix& left, const matrix& right);
  friend bool operator!=(const matrix& left, const matrix& right);

  // Arithmetic operations

  matrix& operator+=(const matrix& other);
  matrix& operator-=(const matrix& other);
  matrix& operator*=(const matrix& other);
  matrix& operator*=(const_reference factor);

  friend matrix operator+(const matrix& left, const matrix& right);
  friend matrix operator-(const matrix& left, const matrix& right);
  friend matrix operator*(const matrix& left, const matrix& right);
  friend matrix operator*(const matrix& left, const_reference right);
  friend matrix operator*(const_reference left, const matrix& right);
};
