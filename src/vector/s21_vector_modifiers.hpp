#ifndef VECTOR_MODIFIERS_H
#define VECTOR_MODIFIERS_H

#include "s21_vector.hpp"

namespace s21 {

template <typename T, typename Alloc>
void vector<T, Alloc>::clear() noexcept {
  if (capacity_) {
    for (size_type i = 0; i < size_; ++i) {
      aTraits::destroy(alloc_, arr_ + i);
    }
    size_ = 0;
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::pop_back() {
  aTraits::destroy(alloc_, arr_ + (size_ - 1));
  --size_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::resize(size_type count) {
  if (count > capacity_) {
    this->reserve(count);
  }

  if (size_ > count) {
    for (; size_ != count;) {
      this->pop_back();
    }
  }

  for (; size_ < count;) {
    aTraits::construct(alloc_, arr_ + size_);
    ++size_;
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::resize(size_type count, const value_type &value) {
  if (count > capacity_) {
    this->reserve(count);
  }

  if (size_ > count) {
    for (; size_ != count;) {
      this->pop_back();
    }
  }

  for (; size_ < count;) {
    aTraits::construct(alloc_, arr_ + size_, value);
    ++size_;
  }
}

template <typename T, typename Alloc>
void vector<T, Alloc>::swap(vector &other) noexcept {
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(alloc_, other.alloc_);
}

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(const_reference value) {
  if (size_ + 1 >= capacity_) {
    capacity_ == 0 ? capacity_ = 1 : capacity_;
    reserve(capacity_ * 2);
  }

  if (size_ < capacity_) {
    aTraits::construct(alloc_, arr_ + size_, value);
  }
  ++size_;
}

template <typename T, typename Alloc>
void vector<T, Alloc>::push_back(T &&value) {
  if (size_ + 1 >= capacity_) {
    capacity_ == 0 ? capacity_ = 1 : capacity_;
    reserve(capacity_ * 2);
  }

  if (size_ < capacity_) {
    aTraits::construct(alloc_, arr_ + size_, value);
  }
  ++size_;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos,
                                                             const T &value) {
  ++size_;
  size_type i = 0;
  vector<T, Alloc>::const_iterator it = this->begin();
  value_type *new_arr = aTraits::allocate(alloc_, size_);
  vector<T, Alloc>::iterator it_res;

  for (; it <= pos; ++it, ++i) {
    aTraits::construct(alloc_, new_arr + i, *it);
  }

  aTraits::construct(alloc_, new_arr + i, value);
  it_res = new_arr + i;
  ++i;

  for (; it != this->cend(); ++it, ++i) {
    aTraits::construct(alloc_, new_arr + i, *it);
  }

  DestroyAndDeallocate(0, size_ - 1, capacity_, arr_, alloc_);
  arr_ = new_arr;
  capacity_ = size_;

  return it_res;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos,
                                                             T &&value) {
  size_type i = 0;
  vector<T, Alloc>::const_iterator it = cbegin();
  value_type *new_arr = nullptr;
  vector<T, Alloc>::iterator it_res;

  try {
    new_arr = aTraits::allocate(alloc_, size_ + 1);

    for (; it <= pos; ++it, ++i) {
      aTraits::construct(alloc_, new_arr + i, *it);
    }

    aTraits::construct(alloc_, new_arr + i, std::move(value));
    it_res = new_arr + i;
    ++i;

    for (; it != this->cend(); ++it, ++i) {
      aTraits::construct(alloc_, new_arr + i, *it);
    }
  } catch (...) {
    DestroyAndDeallocate(0, i, size_ + 1, new_arr, alloc_);
  }

  DestroyAndDeallocate(0, size_ - 1, capacity_, arr_, alloc_);
  arr_ = new_arr;
  capacity_ = size_ = size_ + 1;

  return it_res;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos,
                                                             size_type count,
                                                             const T &value) {
  size_type new_size = size_ + count;
  size_type i = 0;
  bool find_pos = false;
  vector<T, Alloc>::const_iterator it = cbegin();
  vector<T, Alloc>::iterator it_res;
  value_type *new_arr = nullptr;
  try {
    new_arr = aTraits::allocate(alloc_, size_ + count);

    for (; it <= pos; ++it, ++i) {
      aTraits::construct(alloc_, new_arr + i, *it);
    }

    it_res = new_arr + i;
    for (; count > 0; --count, ++i) {
      aTraits::construct(alloc_, new_arr + i, value);
    }

    for (; it != this->cend(); ++it, ++i) {
      aTraits::construct(alloc_, new_arr + i, *it);
    }
  } catch (...) {
    DestroyAndDeallocate(0, i, size_ + count, new_arr, alloc_);
  }

  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  arr_ = new_arr;
  capacity_ = size_ = new_size;

  return it_res;
}

// insert pos, fisrt, last
template <typename T, typename Alloc>
template <class InputIt>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(const_iterator pos,
                                                             InputIt first,
                                                             InputIt last) {
  vector<T, Alloc>::const_iterator it = cbegin();
  vector<T, Alloc>::iterator it_res;
  vector<T, Alloc> res;
  size_type i = 0;

  for (; it <= pos; ++it, ++i) {
    res.push_back(*it);
  }

  it_res = res.arr_ + i;
  for (; first != last; ++first, ++i) {
    res.push_back(*first);
  }

  vector<T, Alloc>::const_iterator it_end = cend();

  for (; it < it_end; ++it, ++i) {
    res.push_back(*it);
  }

  // DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  *this = std::move(res);

  return it_res;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(
    const_iterator pos, std::initializer_list<T> ilist) {
  vector<T, Alloc>::const_iterator it = cbegin();
  vector<T, Alloc>::iterator it_res;
  vector<T, Alloc> res;
  size_type i = 0;

  for (; it <= pos; ++it, ++i) {
    res.push_back(*it);
  }

  it_res = res.arr_ + i;
  size_type size_list = ilist.size();
  for (size_type j = 0; j < size_list; ++j, ++i) {
    res.push_back(*ilist.begin() + j);
  }

  vector<T, Alloc>::const_iterator it_end = cend();

  for (; it < it_end; ++it, ++i) {
    res.push_back(*it);
  }

  // DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  cout << "arr_ = " << arr_ << endl;
  *this = std::move(res);

  return it_res;
}

// Плохая реализация emplace, emplace_back(нет гарантии)
// emplace(...)
template <typename T, typename Alloc>
template <class... Args>
typename vector<T, Alloc>::iterator vector<T, Alloc>::emplace(
    const_iterator pos, Args &&...args) {
  if (pos = cend()) {
    return emplace_back((args)...);
  }

  capacity_ == 0 ? capacity_ = 1 : capacity_;
  reserve(capacity_ * 2);

  vector<T, Alloc>::iterator it_res;
  vector<T, Alloc>::const_iterator it = cbegin();

  for (; it != pos; ++it) {
  }
}

// emplace_back(...)
template <typename T, typename Alloc>
template <class... Args>
typename vector<T, Alloc>::reference vector<T, Alloc>::emplace_back(
    Args &&...args) {
  if (size_ == capacity_) {
    capacity_ == 0 ? capacity_ = 1 : capacity_;
    reserve(capacity_ * 2);
  }

  aTraits::construct(alloc_, arr_ + size_, std::forward<Args>(args)...);
  return arr_[size_++];
}

}  // namespace s21

#endif