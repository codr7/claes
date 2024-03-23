#ifndef CLAES_TYPES_SYM_HPP
#define CLAES_TYPES_SYM_HPP

#include "claes/sym.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Sym: Type::Imp {
    using Value = const claes::Sym *;
    
    static TType<Sym> get() {
      static TType<Sym> t("Sym");
      return t;
    }    

    Sym(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return *left.as(get()) <=> *right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << *value.as(get());
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return *left.as(get()) == *right.as(get());
    }

    virtual void say(const Cell &value, ostream &out) const override {
      out << value.as(get())->name;
    }
  };
}

#endif
