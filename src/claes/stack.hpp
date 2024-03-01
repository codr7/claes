#ifndef CLAES_STACK_HPP
#define CLAES_STACK_HPP

#include <vector>
#include "cell.hpp"


namespace claes {
  struct Stack {
    vector<Cell> items;
    
    Cell pop() {
      auto c = items.back();
      items.pop_back();
      return c;
    }

    void push(const Cell &cell) {
      items.push_back(cell);
    }

    template <typename T>
    void push(TType<T> type, T value) {
      items.emplace_back(type, value);
    }
  };
}

#endif
