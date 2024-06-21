#ifndef VECTOR_CAPACITY_H
#define VECTOR_CAPACITY_H

#include "s21_vector.hpp"

namespace s21 {

// size()
template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const noexcept {
  return size_;
}

// max_size()
template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size()
    const noexcept {
  return aTraits::max_size();
}

// reserve()
template <typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_type new_cap) {
  if (new_cap > capacity_) {
    value_type *new_arr = AllocateMemory(new_cap, size_, arr_, alloc_);
    DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
    arr_ = new_arr;
    capacity_ = new_cap;
  }
}

// capacity()
template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity()
    const noexcept {
  return capacity_;
}

// shrink_to_fit capacity_ == size_
template <typename T, typename Alloc>
void vector<T, Alloc>::shrink_to_fit() {
  value_type *new_arr = AllocateMemory(size_, size_, arr_, alloc_);
  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  capacity_ = size_;
}

// get_allocator()
template <typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator()
    const noexcept {
  return alloc_;
}

}  // namespace s21

#endif