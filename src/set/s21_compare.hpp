#ifndef SRC_S21_COMPARE_H_
#define SRC_S21_COMPARE_H_

namespace s21 {
template <class A>
struct Compare {
  bool less_then(const A &x, const A &y) const { return x < y; }
  bool grater_then(const A &x, const A &y) const { return x > y; }
  bool less_or_equal(const A &x, const A &y) const { return x <= y; }
  bool grater_or_equal(const A &x, const A &y) const { return x >= y; }
  bool eq(const A &x, const A &y) const { return x == y; }
  bool no_eq(const A &x, const A &y) const { return x != y; }
};  // struct Compare
}  // namespace s21
#endif  // SRC_S21_COMPARE_H_
