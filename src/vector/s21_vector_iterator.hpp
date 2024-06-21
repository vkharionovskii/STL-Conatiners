#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

using std::cout;
using std::endl;

namespace s21 {

// Random Access iterator without incheritance
template <bool IsConst, typename T>
class RandomAccessIterator {
 private:
  std::conditional_t<IsConst, const T *, T *> ptr_;

 public:
  using value_type = T;
  using reference_type = T &;
  using pointer_type = T *;
  // using difference_type = RandomAccessIterator::difference_type;
  // using iterator_category = RandomAccessIterator::iterator_category;
  using iterator_category = std::iterator_traits<RandomAccessIterator>;

  using condition =
      typename std::conditional_t<IsConst, const RandomAccessIterator,
                                  RandomAccessIterator>;
  using reference_condition =
      typename std::conditional_t<IsConst, const RandomAccessIterator,
                                  RandomAccessIterator>;

  RandomAccessIterator(T *ptr = nullptr) : ptr_(ptr) {
    // cout << "Parametric constructor Forward iterator called! ptr =  " << ptr_
    //  << endl;
  }

  ~RandomAccessIterator() { ptr_ = nullptr; }
  // overloaded operator*()
  std::conditional_t<IsConst, const T &, T &> operator*() const {
    return *ptr_;
  }

  condition operator->() { return ptr_; }

  // Prefix increment
  reference_condition operator++() {
    ++ptr_;
    return *this;
  }

  // // Postfix increment
  condition operator++(int) {
    RandomAccessIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  reference_condition operator--() {
    --ptr_;
    return *this;
  }

  condition operator--(int) {
    RandomAccessIterator tmp = *this;
    --(*this);
    return tmp;
  }

  std::conditional_t<IsConst, const T &, T &> operator[](std::size_t index) {
    return ptr_[index];
  }

  reference_condition operator+(std::size_t n) {
    ptr_ += n;
    return *this;
  }

  reference_condition operator-(std::size_t n) {
    ptr_ -= n;
    return *this;
  }

  friend bool operator==(const RandomAccessIterator &a,
                         const RandomAccessIterator &b) {
    return a.ptr_ == b.ptr_;
  };

  friend bool operator!=(const RandomAccessIterator &a,
                         const RandomAccessIterator &b) {
    return a.ptr_ != b.ptr_;
  };

  friend bool operator>=(const RandomAccessIterator &a,
                         const RandomAccessIterator &b) {
    return a.ptr_ >= b.ptr_;
  };

  friend bool operator<=(const RandomAccessIterator &a,
                         const RandomAccessIterator &b) {
    return a.ptr_ <= b.ptr_;
  };

  friend bool operator>(const RandomAccessIterator &a,
                        const RandomAccessIterator &b) {
    return a.ptr_ > b.ptr_;
  };

  friend bool operator<(const RandomAccessIterator &a,
                        const RandomAccessIterator &b) {
    return a.ptr_ < b.ptr_;
  };
};

}  // namespace s21

#endif