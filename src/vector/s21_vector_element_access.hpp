#ifndef VECTOR_ELEMENT_ACCESS_H
#define VECTOR_ELEMENT_ACCESS_H

#include "s21_vector.hpp"

namespace s21 {

// at(pos) для non-const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type pos) {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("Index out of range");
  }

  return this.arr_[pos];
}

// at(pos) для const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(
    size_type pos) const {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("Index out of range");
  }

  return arr_[pos];
}

// Перегрузка operator() для non-const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](
    size_type pos) {
  return arr_[pos];
}

// Перегрузка operator() для const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](
    size_type pos) const {
  return arr_[pos];
}

// Метод front() для non-const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
  return arr_[0];
}

// Метод front() для const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
  return arr_[0];
}

// Метод back() для non-const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
  return arr_[size_ - 1];
}

// Метод back() для const объекта
template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
  return arr_[size_ - 1];
}

}  // namespace s21

#endif