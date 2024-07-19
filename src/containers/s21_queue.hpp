#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>

#include "s21_list.hpp"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  list<value_type> que_;

 public:
  queue() : que_() {}
  queue(std::initializer_list<value_type> const &items) : que_() {
    for (auto i = items.begin(); i != items.end(); ++i) {
      push(*(i));
    }
  }
  queue(const queue &q) : que_(q.que_) {}
  queue(queue &&q) : que_(std::move(q.que_)) {}
  ~queue() {}
  queue &operator=(queue &&q) {
    if (this != &q) {
      que_ = q.que_;
    }
    return *this;
  }

  const_reference front() { return que_.front(); }
  const_reference back() { return que_.back(); }

  bool empty() { return que_.empty(); }
  size_type size() { return que_.size(); }

  void push(const_reference value) { que_.push_back(value); }
  void pop() { que_.pop_front(); }
  void swap(queue &other) { que_.swap(other.que_); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    que_.insert_many_back(args...);
  }
};
}  // namespace s21

#endif
