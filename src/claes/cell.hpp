#ifndef CLAES_CELL_HPP
#define CLAES_CELL_HPP

#include <any>
#include "claes/type.hpp"

namespace claes {
  using namespace std;

  struct Cell {
    Type type;
    any value;

    template <typename T, typename V>
    Cell(TType<T> type, const V &value): 
      type(type), value(static_cast<T::Value>(value)) {}

    Cell(const Cell &source): 
      type(source.type), value(source.value) {}
    
    Cell(Cell &&source): 
      type(source.type), value(std::move(source.value)) {}

    template <typename T>
    T as() const { 
      return any_cast<T>(value); 
    }
    
    Cell clone() const {
      return type.clone(*this);
    }

    void dump(ostream &out) const {
      type.dump(*this, out);
    }

    bool is_true() const { 
      return type.is_true(*this); 
    }
  };

  inline bool operator ==(const Cell &left, const Cell &right) {
    if (left.type != right.type) {
      return false;
    }

    return left.type.eq(left, right);
  }

  inline ostream &operator <<(ostream &out, const Cell &cell) {
    cell.dump(out);
    return out;
  }
}

#endif
