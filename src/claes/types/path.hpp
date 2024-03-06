#ifndef CLAES_TYPES_PATH_HPP
#define CLAES_TYPES_PATH_HPP

#include <filesystem>
#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;
  namespace fs = filesystem;

  struct Path: Type::Imp {
    using Value = fs::path;
    
    static TType<Path> get() {
      static TType<Path> t("Path");
      return t;
    }    

    Path(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << value.as(get());
    }

    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return !value.as(get()).empty();
    }
  };
}

#endif
