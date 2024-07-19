#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct BaseNode {
    BaseNode* next_;
    BaseNode* prev_;
  };
  struct Node : BaseNode {
    value_type value_;
  };
  mutable BaseNode fakeNode;
  size_type size_;

 public:
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l);
  list& operator=(const list& l);

  const_reference front();
  const_reference back();

  bool empty() const;
  size_type size();
  size_type max_size();

  void clear();
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void reverse();
  void unique();
  void sort();

  template <typename value_type>
  class ListIterator {
    BaseNode* pos_;
    friend class list<T>;

   public:
    ListIterator() = default;
    ListIterator(BaseNode* node) : pos_(node) {}
    reference operator*() { return (static_cast<Node*>(pos_)->value_); }
    ListIterator& operator++() {
      pos_ = pos_->next_;
      return *this;
      ;
    }
    ListIterator& operator--() {
      pos_ = pos_->prev_;
      return *this;
    }
    bool operator==(const ListIterator& other) { return pos_ == other.pos_; }
    bool operator!=(const ListIterator& other) { return pos_ != other.pos_; }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator() : ListIterator<T>() {}
    ListConstIterator(ListIterator<T> node) : ListIterator<T>(node) {}
    const_reference operator*() {
      return ListIterator<value_type>::operator*();
    }
  };

  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  iterator insert(iterator pos, const_reference value);
  void splice(const_iterator pos, list& other);
  void erase(iterator pos);

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  void quickSort(iterator low, iterator high) noexcept;
  iterator partition(iterator low, iterator high) noexcept;
};

template <typename value_type>
list<value_type>::list() : fakeNode{&fakeNode, &fakeNode}, size_(0) {}

template <typename value_type>
list<value_type>::list(size_type n) : list() {
  for (size_type i = 0; i < n; i++) push_back(value_type());
}

template <typename value_type>
list<value_type>::list(std::initializer_list<value_type> const& items)
    : list() {
  for (auto i = items.begin(); i != items.end(); ++i) push_back(*i);
}

template <typename value_type>
list<value_type>::list(const list& l) : list() {
  for (auto i = l.begin(); i != l.end(); ++i) push_back(*(i));
}

template <typename value_type>
list<value_type>::list(list&& l) : list() {
  fakeNode.next_ = l.fakeNode.next_;
  fakeNode.prev_ = l.fakeNode.prev_;
  l.fakeNode.next_->prev_ = &fakeNode;
  l.fakeNode.prev_->next_ = &fakeNode;
  l.fakeNode.next_ = &(l.fakeNode);
  l.fakeNode.prev_ = &(l.fakeNode);
  size_ = l.size_;
  l.size_ = 0;
}

template <typename value_type>
list<value_type>::~list() {
  while (!empty()) pop_back();
  fakeNode.next_ = &(fakeNode);
  fakeNode.prev_ = &(fakeNode);
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(list&& l) {
  if (this != &l) {
    clear();
    swap(l);
  }
  return *this;
}

template <typename value_type>
list<value_type>& list<value_type>::operator=(const list& l) {
  if (this != &l) {
    list tmp(l);
    clear();
    swap(tmp);
  }
  return *this;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::front() {
  return static_cast<Node*>(fakeNode.next_)->value_;
}

template <typename value_type>
typename list<value_type>::const_reference list<value_type>::back() {
  return static_cast<Node*>(fakeNode.prev_)->value_;
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(fakeNode.next_);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::begin() const {
  return const_iterator(fakeNode.next_);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(&fakeNode);
}

template <typename value_type>
typename list<value_type>::const_iterator list<value_type>::end() const {
  return const_iterator(&fakeNode);
}

template <typename value_type>
bool list<value_type>::empty() const {
  return size_ == 0;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::size() {
  return size_;
}

template <typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(Node) / 2;
}

template <typename value_type>
void list<value_type>::push_back(const_reference value) {
  if (empty())
    push_front(value);
  else {
    Node* node = new Node;
    node->value_ = value;
    node->prev_ = fakeNode.prev_;
    node->next_ = &fakeNode;
    fakeNode.prev_->next_ = node;
    fakeNode.prev_ = node;
    size_++;
  }
}

template <typename value_type>
void list<value_type>::pop_back() {
  if (empty()) return;
  BaseNode* del = fakeNode.prev_;
  del->prev_->next_ = &fakeNode;
  fakeNode.prev_ = del->prev_;
  delete del;
  size_--;
}

template <typename value_type>
void list<value_type>::push_front(const_reference value) {
  Node* node = new Node;
  node->value_ = value;
  if (empty()) {
    fakeNode.prev_ = node;
    fakeNode.next_ = node;
    node->next_ = &fakeNode;
    node->prev_ = &fakeNode;
  } else {
    node->next_ = fakeNode.next_;
    node->prev_ = &fakeNode;
    fakeNode.next_->prev_ = node;
    fakeNode.next_ = node;
  }
  size_++;
}

template <typename value_type>
void list<value_type>::pop_front() {
  if (fakeNode.next_ == &fakeNode) return;
  BaseNode* del = fakeNode.next_;
  del->next_->prev_ = &fakeNode;
  fakeNode.next_ = del->next_;
  delete del;
  size_--;
}

template <typename value_type>
void list<value_type>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  Node* node = new Node;
  node->value_ = value;
  if (empty()) {
    fakeNode.next_ = node;
    fakeNode.prev_ = node;
    node->prev_ = &fakeNode;
    node->next_ = &fakeNode;
  } else {
    node->next_ = pos.pos_;
    node->prev_ = pos.pos_->prev_;
    pos.pos_->prev_->next_ = node;
    pos.pos_->prev_ = node;
  }
  size_++;
  return iterator(node);
}

template <typename value_type>
void list<value_type>::erase(iterator pos) {
  if (empty() || pos.pos_ == nullptr) return;
  if (pos == begin()) {
    fakeNode.next_ = pos.pos_->next_;
    pos.pos_->next_->prev_ = &fakeNode;
  } else {
    pos.pos_->prev_->next_ = pos.pos_->next_;
    pos.pos_->next_->prev_ = pos.pos_->prev_;
  }
  size_--;
  delete pos.pos_;
}

template <typename value_type>
void list<value_type>::swap(list& other) {
  if (other.empty() && empty()) return;
  if (this != &other) {
    if (other.empty()) {
      other.fakeNode.next_ = fakeNode.next_;
      other.fakeNode.prev_ = fakeNode.prev_;
      other.fakeNode.next_->prev_ = &(other.fakeNode);
      other.fakeNode.prev_->next_ = &(other.fakeNode);
      fakeNode.next_ = &(fakeNode);
      fakeNode.prev_ = &(fakeNode);
    } else if (empty()) {
      fakeNode.next_ = other.fakeNode.next_;
      fakeNode.prev_ = other.fakeNode.prev_;
      fakeNode.next_->prev_ = &fakeNode;
      fakeNode.prev_->next_ = &fakeNode;
      other.fakeNode.next_ = &(other.fakeNode);
      other.fakeNode.prev_ = &(other.fakeNode);
    } else {
      std::swap(fakeNode.next_, other.fakeNode.next_);
      std::swap(fakeNode.prev_, other.fakeNode.prev_);
      fakeNode.next_->prev_ = &(fakeNode);
      fakeNode.prev_->next_ = &(fakeNode);
      other.fakeNode.next_->prev_ = &(other.fakeNode);
      other.fakeNode.prev_->next_ = &(other.fakeNode);
    }
    std::swap(size_, other.size_);
  }
}

template <typename value_type>
void list<value_type>::merge(list& other) {
  if (other.empty() || this == &other) return;
  if (empty()) {
    swap(other);
    return;
  }

  iterator iter1 = begin();
  iterator iter2 = other.begin();
  while (iter1 != end() && iter2 != other.end()) {
    if (*(iter1) >= *(iter2)) {
      insert(iter1, *(iter2));
      ++iter2;
    } else
      ++iter1;
  }

  while (iter2 != other.end()) {
    insert(iter1, *(iter2));
    ++iter2;
  }
  other.clear();
}

template <typename value_type>
void list<value_type>::splice(const_iterator pos, list& other) {
  if (!other.empty()) {
    for (iterator i = other.begin(); i != other.end(); ++i) insert(pos, *(i));
    other.clear();
  }
}

template <typename value_type>
void list<value_type>::reverse() {
  if (empty()) return;
  BaseNode* cur = fakeNode.next_;
  for (size_type i = 0; i < size_; i++) {
    std::swap(cur->next_, cur->prev_);
    cur = cur->prev_;
  }
  std::swap(fakeNode.prev_, fakeNode.next_);
}

template <typename value_type>
void list<value_type>::unique() {
  for (iterator cur = begin(); cur != end();) {
    iterator next = cur.pos_->next_;
    if (next != end() && *(cur) == *(next)) {
      erase(next);
    } else {
      ++cur;
    }
  }
}

template <typename value_type>
void list<value_type>::sort() {
  if (size_ > 1) {
    quickSort(begin(), --end());
  }
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::partition(
    iterator low, iterator high) noexcept {
  value_type pivot = *(high);
  iterator i = low.pos_->prev_;

  for (iterator j = low; j != high; ++j) {
    if (*(j) < pivot) {
      i = (i == end()) ? low : ++i;
      std::swap(*(i), *(j));
    }
  }
  i = (i == end()) ? low : ++i;
  std::swap(*(i), *(high));

  return i;
}

template <typename value_type>
void list<value_type>::quickSort(iterator low, iterator high) noexcept {
  if (high != end() && low != end() && low != high.pos_->next_) {
    iterator pivot = partition(low, high);
    quickSort(low, pivot.pos_->prev_);
    quickSort(pivot.pos_->next_, high);
  }
}

template <typename value_type>
template <typename... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args&&... args) {
  for (auto arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    push_back(arg);
  }
}

template <typename value_type>
template <typename... Args>
void list<value_type>::insert_many_front(Args&&... args) {
  for (auto arg : {args...}) {
    push_front(arg);
  }
}

}  // namespace s21

#endif