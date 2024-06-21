#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <list>
#include <vector>

#include "s21_vector_iterator.hpp"

// using std::cout;
// using std::endl;

namespace s21 {
template <typename T = int, typename Alloc = std::allocator<T>>
class vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using allocator_type = Alloc;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using aTraits = std::allocator_traits<Alloc>;
  using const_reference = const value_type &;
  using pointer = typename std::allocator_traits<Alloc>::pointer;
  using const_pointer = typename std::allocator_traits<Alloc>::const_pointer;

 private:
  // Выделяет память и конструирует size объектов со значением value
  static value_type *AllocateMemory(size_type capacity, size_type size,
                                    const_reference value, Alloc &alloc);
  // Выделяет память и конструирует копирует size объектов из old_arr в new_arr
  static value_type *AllocateMemory(size_type capacity, size_type size,
                                    const value_type *old_arr, Alloc &alloc);

  static value_type *AllocateMemory(size_type capacity, size_type size,
                                    Alloc &alloc);

  // Вызывает деструкторы от start до end и освобождает память, выделенную под
  // new_arr
  static void DestroyAndDeallocate(size_type start, size_type end,
                                   size_type capacity, value_type *new_arr,
                                   Alloc &alloc);

 public:
  T *arr_;
  size_t size_;
  size_t capacity_;
  Alloc alloc_;

  vector();

  vector(const Alloc &alloc);

  vector(size_type count, const T &value, const Alloc &alloc = Alloc());

  // vector() noexcept(noexcept(Alloc())) : alloc_(Alloc());
  // explicit vector(const Alloc &alloc) noexcept : alloc_(alloc) {}

  explicit vector(size_type count, const Alloc &alloc = Alloc());
  template <class InputIt>
  vector(InputIt first, InputIt last, const Alloc &alloc = Alloc());
  vector(const vector &copy, const Alloc &alloc);
  vector(vector &&other) noexcept;
  vector(vector &&offset, const Alloc &alloc);
  vector(std::initializer_list<T> init, const Alloc &alloc = Alloc());

  vector(const vector &copy);
  ~vector();

  vector &operator=(const vector &other);
  vector &operator=(vector &&other) noexcept;
  vector &operator=(std::initializer_list<T> ilist);

  void assign(size_type count, const T &value);
  template <class InputIt>
  void assign(InputIt first, InputIt last);
  void assign(std::initializer_list<T> ilist);

  allocator_type get_allocator() const noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  reference front();
  const_reference front() const;

  reference back();
  const_reference back() const;

  T *data() noexcept { return arr_; }
  const T *data() const noexcept { return arr_; }

  using iterator = RandomAccessIterator<false, T>;
  using const_iterator = RandomAccessIterator<true, T>;

  iterator begin() noexcept { return iterator(arr_); }
  const_iterator begin() const noexcept { return const_iterator(arr_); }
  const_iterator cbegin() const noexcept { return const_iterator(arr_); }

  iterator end() noexcept { return iterator(arr_ + size_); }
  const_iterator end() const noexcept { return const_iterator(&arr_ + size_); }
  const_iterator cend() const noexcept { return const_iterator(arr_ + size_); }

  bool empty() const noexcept { return (begin() == end()); }

  size_type size() const noexcept;

  size_type max_size() const noexcept;

  void reserve(size_type new_cap);

  size_type capacity() const noexcept;

  void shrink_to_fit();

  void clear() noexcept;

  iterator insert(const_iterator pos, const T &value);
  iterator insert(const_iterator pos, T &&value);
  iterator insert(const_iterator pos, size_type count, const T &value);
  template <class InputIt>
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  iterator insert(const_iterator pos, std::initializer_list<T> ilist);

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  void erase(iterator pos);
  // iterator erase(const_iterator first, const_iterator last);

  template <class... Args>
  reference emplace_back(Args &&...args);

  void push_back(const_reference value);
  void push_back(T &&value);

  void pop_back();

  void resize(size_type count);
  void resize(size_type count, const value_type &value);
  void swap(vector &other) noexcept;
};

}  // namespace s21

#include "non_member_functions.hpp"
#include "s21_vector_capacity.hpp"
#include "s21_vector_constructor.hpp"
#include "s21_vector_element_access.hpp"
#include "s21_vector_modifiers.hpp"
#include "s21_vector_operator.hpp"
// #include "vector_iterator.hpp"

#endif