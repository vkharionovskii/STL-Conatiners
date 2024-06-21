#ifndef VECTOR_OPERATOR_H
#define VECTOR_OPERATOR_H

#include "s21_vector.hpp"

namespace s21 {

// оператор=() копирующий
template <typename T, typename Alloc>
typename vector<T, Alloc>::vector &vector<T, Alloc>::operator=(
    const vector &other) {
  if (this == &other) {
    return *this;
  }

  Alloc tmp_alloc = other.alloc_;

  value_type *new_arr =
      AllocateMemory(other.capacity_, other.size_, other.arr_, tmp_alloc);

  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);

  arr_ = new_arr;
  size_ = other.size_;
  capacity_ = other.capacity_;
  alloc_ = std::move(tmp_alloc);

  return *this;
}

// оператор=() перемещающий
template <typename T, typename Alloc>
typename vector<T, Alloc>::vector &vector<T, Alloc>::operator=(
    vector &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);

  arr_ = other.arr_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  alloc_ = std::move(other.alloc_);

  other.arr_ = nullptr;
  other.size_ = other.capacity_ = 0;

  return *this;
}

// Метод assign()
template <typename T, typename Alloc>
void vector<T, Alloc>::assign(size_type count, const T &value) {
  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  size_ = capacity_ = 0;

  arr_ = AllocateMemory(count, count, value, alloc_);
  size_ = capacity_ = count;
}

// Метод assign() от init_list
template <typename T, typename Alloc>
void vector<T, Alloc>::assign(std::initializer_list<T> ilist) {
  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  size_ = capacity_ = 0;

  size_type i = 0;
  size_type new_size = ilist.size();
  arr_ = AllocateMemory(new_size, new_size, alloc_);
  try {
    for (; i < new_size; ++i) {
      aTraits::construct(alloc_, arr_ + i, *(ilist.begin() + i));
    }
    size_ = capacity_ = new_size;
  } catch (...) {
    DestroyAndDeallocate(0, new_size, new_size, arr_, alloc_);
    arr_ = nullptr;
    size_ = capacity_ = 0;
  }
}

template <typename T, typename Alloc>
template <class InputIt>
void vector<T, Alloc>::assign(InputIt first, InputIt last) {
  value_type *new_arr = aTraits::allocate(alloc_, capacity_);
  size_type i = 0;

  for (; first != last; ++first, ++i) {
    aTraits::construct(alloc_, new_arr + i, *first);
  }

  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);

  arr_ = new_arr;
  size_ = i;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::vector &vector<T, Alloc>::operator=(
    std::initializer_list<T> ilist) {
  Alloc new_alloc = aTraits::select_on_container_copy_construction(alloc_);
  size_type new_size = ilist.size();
  value_type *new_arr = AllocateMemory(new_size, new_size, new_alloc);

  size_type i = 0;
  try {
    for (; i < new_size; ++i) {
      aTraits::construct(new_alloc, new_arr + i, *(ilist.begin() + i));
    }

    DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
    arr_ = new_arr;
    size_ = capacity_ = new_size;
    alloc_ = std::move(new_alloc);
  } catch (...) {
    DestroyAndDeallocate(0, i, new_size, arr_, new_alloc);
  }

  return *this;
}

}  // namespace s21

#endif