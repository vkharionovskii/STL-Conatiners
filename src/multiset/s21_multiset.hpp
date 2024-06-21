#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include "../set/s21_compare.hpp"
#include "../set/s21_node_tree.hpp"
#include "../set/s21_set.hpp"
#include "../set/s21_tree_iterator.hpp"

namespace s21 {
template <class Key, class Compare = s21::Compare<Key>>
class multiset : public s21::set<Key, Compare> {
  using cmp_type = Compare;
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using node_t = NodeTree<Key, cmp_type>;
  using node_p = typename set<value_type, cmp_type>::node_p;
  using iterator = TreeIterator<value_type, cmp_type>;
  using size_type = size_t;

 public:
  multiset() : set<key_type, cmp_type>() {}
  multiset(std::initializer_list<value_type> const &items)
      : multiset<key_type, cmp_type>() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      this->insert(*it);
    }
  }
  multiset(const multiset &ms) : multiset<key_type, cmp_type>() {
    this->set_copy(ms.root_);
    this->size_ = ms.size_;
  }
  multiset(multiset &&ms) : multiset<key_type, cmp_type>() {
    if (this->root_ != ms.root_) {
      delete this->nill_;
      this->root_ = ms.root_;
      this->nill_ = ms.nill_;
      this->size_ = ms.size_;
      ms.root_ = nullptr;
      ms.nill_ = nullptr;
      ms.size_ = 0;
    }
  }
  ~multiset() = default;

  std::pair<iterator, bool> insert(const value_type &value) {
    bool bool_res = true;
    std::pair<iterator, bool> my_pair = this->InsertIthem(value);
    return my_pair;
  }

  void merge(multiset &other) {
    if (other.size_ > 0) {
      for (auto i : other) insert(i);
    }
  }

  /******************************** Multiset Lookup
   * ***********************************************/

  size_type count(const Key &key) {
    size_type count = 0;
    for (auto it : *this) {
      if (it == key) {
        ++count;
      }
    }
    return count;
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    auto it_begin = this->find(key);
    auto it_end = it_begin;
    while (*(it_end) == key) {
      ++it_end;
    }
    return {it_begin, it_end};
  }

  iterator lower_bound(const Key &key) {
    auto res_elem = this->find(key);
    if (*res_elem != key) {
      find_next(res_elem, key);
    }
    return res_elem;
  }

  iterator upper_bound(const Key &key) {
    auto res_elem = this->find(key);
    if (*res_elem != key) {
      find_next(res_elem, key);
    } else {
      while (*res_elem == key) ++res_elem;
    }
    return res_elem;
  }

 private:
  void find_next(iterator &res_elem, const Key &key) {
    auto elem = res_elem;
    while (this->comp_.less_then(*elem, key) && elem != this->end()) {
      elem++;
    }
    res_elem = elem;
  }

  std::pair<node_p, bool> insertIthem_(node_p currentNode, node_p newNode) {
    std::pair<node_p, bool> pair_res = {nullptr, true};
    newNode->parent_ = currentNode;
    if (this->comp_.less_or_equal(newNode->key_, currentNode->key_)) {
      pair_res = this->add_node(currentNode->left_, newNode);
    } else if (this->comp_.grater_then(newNode->key_, currentNode->key_)) {
      pair_res = this->add_node(currentNode->right_, newNode);
    }
    return pair_res;
  }

  std::pair<node_p, bool> InsertIthem(const key_type &NewKey) {
    std::pair<node_p, bool> pair_res = {nullptr, true};
    node_p NewNode = new node_t(NewKey, nullptr, this->nill_, this->nill_);
    this->size_ += 1;
    if (this->root_ == nullptr) {
      (this->root_) = NewNode;
      pair_res = {(this->root_), true};
    } else {
      pair_res = this->insertIthem_(this->root_, NewNode);
    }
    return pair_res;
  }

  std::pair<node_p, bool> add_node(node_p &currentNode, node_p &newNode) {
    std::pair<node_p, bool> pair_res;
    if (currentNode == this->nill_) {
      currentNode = newNode;
      pair_res = {currentNode, true};
    } else {
      pair_res = this->insertIthem_(currentNode, newNode);
    }
    return pair_res;
  }

  void set_copy(node_p other) {
    this->InsertIthem(other->key_);
    if (other->left_ != other->get_nill()) this->set_copy(other->left_);
    if (other->right_ != other->get_nill()) this->set_copy(other->right_);
  }
};  // mustiset
}  // namespace s21

#endif  // SRC_S21_MULTISET_H_
