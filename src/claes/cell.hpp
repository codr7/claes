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
    Cell(TType<T> type, const V &value): type(type), value(static_cast<V>(value)) {}

    Cell(const Cell &source): type(source.type), value(source.value) {}
    Cell(Cell &&source): type(source.type), value(std::move(source.value)) {}
  };
}

#endif
