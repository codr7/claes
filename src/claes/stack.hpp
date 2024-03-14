#ifndef CLAES_STACK_HPP
#define CLAES_STACK_HPP

#include <vector>
#include "cell.hpp"


namespace claes {
  struct Stack {
    vector<Cell> items;
    
    bool empty() const {
      return items.empty();
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
