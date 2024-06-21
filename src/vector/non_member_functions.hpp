#ifndef NON_MEMBER_FUNCTIONS_H
#define NON_MEMBER_FUNCTIONS_H

#include "s21_vector.hpp"

namespace s21 {

template <class T, class Alloc>
bool operator==(const s21::vector<T, Alloc> &lhs,
                const s21::vector<T, Alloc> &rhs) {
  if (lhs.size_ != rhs.size_) {
    return false;
  }

  for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size_; ++i) {
    if (lhs.arr_[i] != rhs.arr_[i]) {
      return false;
    }
  }

  return true;
}

template <class T, class Alloc>
bool operator!=(const s21::vector<T, Alloc> &lhs,
                const s21::vector<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<(const s21::vector<T, Alloc> &lhs,
               const s21::vector<T, Alloc> &rhs) {
  for (typename vector<T, Alloc>::size_type i = 0; i < lhs.size_; ++i) {
    if (lhs.arr_[i] < rhs.arr_[i]) {
      return true;
    }
  }

  return false;
}

template <class T, class Alloc>
bool operator<=(const s21::vector<T, Alloc> &lhs,
                const s21::vector<T, Alloc> &rhs) {
  return !(lhs > rhs);
}

template <class T, class Alloc>
bool operator>(const s21::vector<T, Alloc> &lhs,
               const s21::vector<T, Alloc> &rhs) {
  return rhs < lhs;
}

template <class T, class Alloc>
bool operator>=(const s21::vector<T, Alloc> &lhs,
                const s21::vector<T, Alloc> &rhs) {
  return !(lhs < rhs);
}
}  // namespace s21

#endif