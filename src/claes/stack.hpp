#ifndef CLAES_STACK_HPP
#define CLAES_STACK_HPP

#include <vector>
#include "cell.hpp"


namespace claes {
  struct Stack {
    using Items = vector<Cell>;
    
    Items items;

    Items::iterator begin() {
      return items.begin();
    }

    Items::const_iterator begin() const {
      return items.begin();
    }

    bool empty() const {
      return items.empty();
    }

    Items::iterator end() {
      return items.end();
    }

    Items::const_iterator end() const {
      return items.end();
    }

    Cell &peek() {
      return items.back();
    }

    const Cell &peek() const {
      return items.back();
    }

    Cell pop() {
      auto c = items.back();
      items.pop_back();
      return c;
    }

    void push(const Cell &cell) {
      items.push_back(cell);
    }

    template <typename T, typename V>
    void push(TType<T> type, const V &value) {
      items.emplace_back(type, value);
    }

    size_t len() const {
      return items.size();
    }
  };

  inline ostream &operator<<(ostream &out, const Stack &s) {
    out << '[';
    auto i = 0;
    
    for (const auto &v: s.items) {
      if (i++) {
	out << ' ';
      }
      
      out << v;
    }
    
    out << ']';
    return out;
  }
}

#endif
