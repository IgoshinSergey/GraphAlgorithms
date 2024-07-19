#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>

#include "s21_list.hpp"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  list<T> node_;

 public:
  stack() : node_() {}
  stack(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i) {
      push(*(i));
    }
  }
  stack(const stack &s) : node_(s.node_) {}
  stack(stack &&s) : node_(std::move(s.node_)) {}
  ~stack() {}
  stack &operator=(stack &&s) {
    if (this != &s) {
      node_ = s.node_;
    }
    return *this;
  }

  const_reference top() { return node_.back(); }
  bool empty() { return node_.empty(); }

  size_type size() { return node_.size(); }
  void push(const_reference value) { node_.push_back(value); }
  void pop() { node_.pop_back(); }
  void swap(stack &other) { node_.swap(other.node_); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    node_.insert_many_back(args...);
  }
};
}  // namespace s21

#endif