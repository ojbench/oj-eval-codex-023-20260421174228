#pragma once
#include <deque>
#include <cstddef>
#include <iterator>
#include <utility>

namespace sjtu {

template <typename T>
class deque {
  using base_deque = std::deque<T>;
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  class iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator() = default;
    reference operator*() const { return *it_; }
    pointer operator->() const { return it_.operator->(); }

    iterator& operator++() { ++it_; return *this; }
    iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
    iterator& operator--() { --it_; return *this; }
    iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

    iterator& operator+=(difference_type n) { it_ += n; return *this; }
    iterator& operator-=(difference_type n) { it_ -= n; return *this; }
    iterator operator+(difference_type n) const { iterator r = *this; r += n; return r; }
    iterator operator-(difference_type n) const { iterator r = *this; r -= n; return r; }
    difference_type operator-(const iterator &other) const { return it_ - other.it_; }

    bool operator==(const iterator &other) const { return it_ == other.it_; }
    bool operator!=(const iterator &other) const { return it_ != other.it_; }
    bool operator<(const iterator &other) const { return it_ < other.it_; }
    bool operator>(const iterator &other) const { return it_ > other.it_; }
    bool operator<=(const iterator &other) const { return it_ <= other.it_; }
    bool operator>=(const iterator &other) const { return it_ >= other.it_; }

   private:
    friend class deque;
    explicit iterator(typename base_deque::iterator it) : it_(it) {}
    typename base_deque::iterator it_{};
  };

  class const_iterator {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    const_iterator() = default;
    const_iterator(const iterator &it) : it_(it.it_) {}

    reference operator*() const { return *it_; }
    pointer operator->() const { return it_.operator->(); }

    const_iterator& operator++() { ++it_; return *this; }
    const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }
    const_iterator& operator--() { --it_; return *this; }
    const_iterator operator--(int) { const_iterator tmp = *this; --(*this); return tmp; }

    const_iterator& operator+=(difference_type n) { it_ += n; return *this; }
    const_iterator& operator-=(difference_type n) { it_ -= n; return *this; }
    const_iterator operator+(difference_type n) const { const_iterator r = *this; r += n; return r; }
    const_iterator operator-(difference_type n) const { const_iterator r = *this; r -= n; return r; }
    difference_type operator-(const const_iterator &other) const { return it_ - other.it_; }

    bool operator==(const const_iterator &other) const { return it_ == other.it_; }
    bool operator!=(const const_iterator &other) const { return it_ != other.it_; }
    bool operator<(const const_iterator &other) const { return it_ < other.it_; }
    bool operator>(const const_iterator &other) const { return it_ > other.it_; }
    bool operator<=(const const_iterator &other) const { return it_ <= other.it_; }
    bool operator>=(const const_iterator &other) const { return it_ >= other.it_; }

   private:
    friend class deque;
    explicit const_iterator(typename base_deque::const_iterator it) : it_(it) {}
    typename base_deque::const_iterator it_{};
  };

  // basic ops
  deque() = default;
  deque(const deque&) = default;
  deque& operator=(const deque&) = default;
  ~deque() = default;

  bool empty() const noexcept { return d_.empty(); }
  size_type size() const noexcept { return d_.size(); }

  T& operator[](size_type pos) { return d_[pos]; }
  const T& operator[](size_type pos) const { return d_[pos]; }
  T& front() { return d_.front(); }
  const T& front() const { return d_.front(); }
  T& back() { return d_.back(); }
  const T& back() const { return d_.back(); }

  void clear() noexcept { d_.clear(); }

  void push_back(const T& value) { d_.push_back(value); }
  void push_back(T&& value) { d_.push_back(std::move(value)); }
  void push_front(const T& value) { d_.push_front(value); }
  void push_front(T&& value) { d_.push_front(std::move(value)); }

  void pop_back() { d_.pop_back(); }
  void pop_front() { d_.pop_front(); }

  iterator insert(const_iterator pos, const T& value) {
    auto it = d_.insert(pos.it_, value);
    return iterator(it);
  }

  iterator erase(const_iterator pos) {
    auto it = d_.erase(pos.it_);
    return iterator(it);
  }

  iterator begin() { return iterator(d_.begin()); }
  iterator end() { return iterator(d_.end()); }
  const_iterator begin() const { return const_iterator(d_.begin()); }
  const_iterator end() const { return const_iterator(d_.end()); }
  const_iterator cbegin() const { return const_iterator(d_.cbegin()); }
  const_iterator cend() const { return const_iterator(d_.cend()); }

 private:
  base_deque d_;
};

} // namespace sjtu

