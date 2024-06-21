#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <initializer_list>
#include <iostream>
using namespace std;

namespace s21 {
template <typename T, size_t N>
class array {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

 private:
  size_type size_;
  value_type data_[N];

 public:
  array() : size_(N) {}  // default constructor
  array(std::initializer_list<value_type> const &items) : array() {
    if (size_ < items.size())
      throw std::out_of_range("Too many initializers for s21::array");
    size_type i = 0;
    for (auto it = items.begin(); it != items.end(); it++, i++) {
      data_[i] = *it;
    }
  }
  array(const array &other) : array() {
    std::copy(other.cbegin(), other.cend(), data_);
  }
  array(array &&other) : array() {
    std::move(other.cbegin(), other.cend(), data_);
  }

  ~array() {}

  void operator=(array &other) {
    std::copy(other.cbegin(), other.cend(), data_);
  }
  void operator=(array &&other) {
    std::move(other.cbegin(), other.cend(), data_);
  }

  // Array Element access
  reference at(size_type pos) {
    if (pos > size_) throw std::runtime_error("element does not exist");
    return data_[pos];
  }
  reference operator[](size_type pos) { return data_[pos]; }
  const_reference front() { return data_[0]; }
  const_reference back() { return data_[size_ - 1]; }
  iterator data() { return data_; }

  // Array Iterators
  iterator begin() noexcept { return &data_[0]; }
  iterator end() noexcept { return &data_[size_]; }
  const_iterator cbegin() const noexcept { return &data_[0]; }
  const_iterator cend() const noexcept { return &data_[size_]; }

  // Array Capacity
  bool empty() { return ((size_ == 0) ? true : false); }
  size_type size() { return size_; }
  size_type max_size() { return size_; }

  // Array Modifiers
  void swap(array &other) {
    if ((size_ != other.size_) ||
        (typeid(data_).name() != typeid(other.data_).name()))
      throw std::runtime_error("type 1st != type 2nd");

    s21::array<T, N> tmp;
    for (int i = 0; i < size_; ++i) {
      tmp.data_[i] = data_[i];
    }
    for (int i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
    for (int i = 0; i < size_; ++i) {
      other.data_[i] = tmp.data_[i];
    }
    tmp.~array();
  }

  void fill(const_reference value) {
    for (auto &elem : data_) {
      elem = value;
    }
  }
};
}  // namespace s21

#endif  // S21_ARRAY_H
