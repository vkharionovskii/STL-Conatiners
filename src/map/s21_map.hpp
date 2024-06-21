#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include "../map/s21_pair_compare.hpp"
#include "../set/s21_node_tree.hpp"
#include "../set/s21_set.hpp"
#include "../set/s21_tree_iterator.hpp"

namespace s21 {
template <class Key, class T, class Compare = PairCompare<Key, T>>
class map : public set<std::pair<Key, T>, Compare> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using cmp_type = Compare;
  using iterator = TreeIterator<value_type, cmp_type>;
  using node_t = NodeTree<Key, cmp_type>;
  using node_p = typename s21::set<value_type, cmp_type>::node_p;

  map() : set<value_type, cmp_type>() {}
  map(std::initializer_list<value_type> const &items)
      : set<value_type, cmp_type>(items) {}
  map(const map &other) : set<value_type, cmp_type>(other) {}
  map(map &&m) : set<value_type, cmp_type>(m) {}
  ~map() {}

  void operator=(map &&m) {
    this->clear();
    s21::set<value_type, cmp_type>::set_copy(m.root_);
    m.clear();
  }

  /************************ Map Element access ********************************/

  mapped_type &at(const Key &key) {
    auto res = find_pair(key);
    if (res.second == false) {
      throw std::out_of_range("map::at");
    }
    return res.first;
  }

  std::pair<mapped_type &, bool> find_pair(const Key &key) {
    bool el_exist = true;
    node_p base = this->root_;
    while (base->key_.first != key && base != this->nill_) {
      if (base->key_.first > key) {
        base = base->left_;
      } else {
        base = base->right_;
      }
    }
    if (base == this->nill_) {
      el_exist = false;
    }
    return {(base->key_.second), el_exist};
  }

  mapped_type &operator[](const Key &key) {
    std::pair<mapped_type, bool> *res = new std::pair<mapped_type, bool>;
    *res = find_pair(key);
    if (res->second == false) {
      this->insert({key, 0});
      res->first = 0;
    }
    return res->first;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return s21::set<value_type, cmp_type>::insert(value);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    std::pair<Key, T> pair = {key, obj};
    return this->insert(pair);
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    std::pair<iterator, bool> res;
    bool elem_exist = false;
    for (auto it : *this) {
      if (it.first == key) {
        this->at(key) = obj;
        elem_exist = true;
        break;
      }
    }
    if (elem_exist == false) {
      res = this->insert(key, obj);
    }
    return res;
  }

};  // map
}  // namespace s21
#endif  // SRC_S21_MAP_H_
