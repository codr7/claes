#ifndef CLAES_CELL_HPP
#define CLAES_CELL_HPP

#include <any>
#include "claes/type.hpp"

namespace claes {
  using namespace std;

  struct Cell {
    Type type;
    any value;

    template <typename T>
    Cell(TType<T> type, T value): type(type), value(value) {}

    Cell(const Cell &source): type(source.type), value(source.value) {}
    Cell(Cell &&source): type(source.type), value(std::move(source.value)) {}
  };
}

#endif
