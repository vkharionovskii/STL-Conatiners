#ifndef VECTOR_CONSTRUCTOR_H
#define VECTOR_CONSTRUCTOR_H

#include "s21_vector.hpp"

namespace s21 {

// Конструктор по умолчанию
template <typename T, typename Alloc>
vector<T, Alloc>::vector()
    : arr_(nullptr), size_(0), capacity_(0), alloc_(Alloc()) {}

// Конструктор с заданным аллокатором
template <typename T, typename Alloc>
vector<T, Alloc>::vector(const Alloc &alloc)
    : arr_(nullptr), size_(0), capacity_(0), alloc_(alloc) {}

// Конструктор с количеством элементов, значением по умолчанию и аллокатором
template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type count, const T &value, const Alloc &alloc)
    : alloc_(alloc) {
  arr_ = AllocateMemory(count, count, value, alloc_);
  size_ = capacity_ = count;
}

// Конструктор с количеством элементов и аллокатором
template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type count, const Alloc &alloc)
    : arr_(nullptr), alloc_(alloc) {
  arr_ = AllocateMemory(count, count, alloc_);
  size_ = capacity_ = count;
}

// Конструктор перемещения с заданным аллокатором
template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector &&offset, const Alloc &alloc) : alloc_(alloc) {
  size_type i = 0;
  if (capacity_ > 0) {
    try {
      arr_ = aTraits::allocate(alloc_, offset.capacity_);
      for (; i < offset.size_; ++i) {
        aTraits::construct(alloc_, arr_ + i, std::move(offset.arr_[i]));
      }
    } catch (...) {
      DestroyAndDeallocate(0, i, offset.capacity_, arr_, alloc_);
    }
  }
}

// Конструктор копирования
template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &copy) : alloc_(copy.alloc_) {
  if (this != &copy) {
    arr_ = AllocateMemory(copy.capacity_, copy.size_, copy.arr_, alloc_);
  }
  size_ = copy.size_;
  capacity_ = copy.capacity_;
}

// Конструктор перемещения
template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector &&offset) noexcept
    : arr_(offset.arr_),
      size_(offset.size_),
      capacity_(offset.capacity_),
      alloc_(offset.alloc_) {
  offset.size_ = 0;
  offset.capacity_ = 0;
  offset.arr_ = nullptr;
  offset.alloc_ = Alloc();
}

// Конструктор копирования c pfllfyysv fkjrfnjhjv
template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &copy, const Alloc &alloc)
    : alloc_(alloc) {
  if (this != &copy) {
    arr_ = AllocateMemory(copy.capacity_, copy.size_, copy.arr_, alloc_);
  }
  size_ = copy.size_;
  capacity_ = copy.capacity_;
}

// Деструктор
template <typename T, typename Alloc>
vector<T, Alloc>::~vector() {
  DestroyAndDeallocate(0, size_, capacity_, arr_, alloc_);
  size_ = capacity_ = 0;
}

// Allocate Memory выделяет память и коструирует объекты с значением value
template <typename T, typename Alloc>
typename vector<T, Alloc>::value_type *vector<T, Alloc>::AllocateMemory(
    size_type capacity, size_type size, const_reference value, Alloc &alloc) {
  value_type *new_arr = nullptr;
  if (capacity > 0) {
    size_type i = 0;
    try {
      new_arr = aTraits::allocate(alloc, capacity);
      for (; i < size; ++i) {
        aTraits::construct(alloc, new_arr + i, value);
      }
    } catch (...) {
      DestroyAndDeallocate(0, i, capacity, new_arr, alloc);
      throw;
    }
  }
  return new_arr;
}

// Allocate Memory выделяет память и копирует объекты из old_arr
template <typename T, typename Alloc>
typename vector<T, Alloc>::value_type *vector<T, Alloc>::AllocateMemory(
    size_type capacity, size_type size, const value_type *old_arr,
    Alloc &alloc) {
  value_type *new_arr = nullptr;
  if (capacity > 0) {
    size_type i = 0;
    try {
      new_arr = aTraits::allocate(alloc, capacity);
      for (; i < size; ++i) {
        aTraits::construct(alloc, new_arr + i, old_arr[i]);
      }
    } catch (...) {
      DestroyAndDeallocate(0, i, capacity, new_arr, alloc);
      throw;
    }
  }
  return new_arr;
}

// Allocate Memory выделяет память и коструирует объекты по умолчанию
template <typename T, typename Alloc>
typename vector<T, Alloc>::value_type *vector<T, Alloc>::AllocateMemory(
    size_type capacity, size_type size, Alloc &alloc) {
  value_type *new_arr = nullptr;
  if (capacity > 0) {
    size_type i = 0;
    try {
      new_arr = aTraits::allocate(alloc, capacity);
      for (; i < size; ++i) {
        aTraits::construct(alloc, new_arr + i);
      }
    } catch (...) {
      DestroyAndDeallocate(0, i, capacity, new_arr, alloc);
      throw;
    }
  }
  return new_arr;
}

// Destroy And Deallocate
template <typename T, typename Alloc>
void vector<T, Alloc>::DestroyAndDeallocate(size_type start, size_type end,
                                            size_type capacity,
                                            value_type *new_arr, Alloc &alloc) {
  if (new_arr) {
    for (; start < end; ++start) {
      aTraits::destroy(alloc, new_arr + start);
    }

    aTraits::deallocate(alloc, new_arr, capacity);
  }

  new_arr = nullptr;
  alloc = Alloc();
}

// Конструктор с двумя итераторами First и Last
// template <typename T, typename Alloc>
// template <class InputIt>
// vector<T, Alloc>::vector(InputIt first, InputIt last, const Alloc &alloc)
//     : alloc_(alloc) {

//     }

// Конструктор с листом инициализации для вектора
template <typename T, typename Alloc>
vector<T, Alloc>::vector(std::initializer_list<T> init, const Alloc &alloc)
    : size_(init.size()), capacity_(size_), alloc_(alloc) {
  arr_ = AllocateMemory(size_, size_, alloc_);
  size_type i = 0;

  try {
    for (; i < size_; ++i) {
      aTraits::construct(alloc_, arr_ + i, *(init.begin() + i));
    }
  } catch (...) {
    DestroyAndDeallocate(0, i, capacity_, arr_, alloc_);
    size_ = capacity_ = 0;
  }
}

template <typename T, typename Alloc>
template <class InputIt>
vector<T, Alloc>::vector(InputIt first, InputIt last, const Alloc &alloc)
    : arr_(nullptr), size_(0), capacity_(0), alloc_(alloc) {
  cout << "Hello" << endl;
  for (; first != last; ++first) {
    this->push_back(*first);
  }
}

}  // namespace s21

#endif