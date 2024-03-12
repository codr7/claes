#ifndef CLAES_TYPES_STRING_HPP
#define CLAES_TYPES_STRING_HPP

#include "claes/types/rune.hpp"

namespace claes::types {
  using namespace claes;

  struct String: Type::Imp {
    using Value = string;
    
    static TType<String> get() {
      static TType<String> t("String");
      return t;
    }    

    String(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '"' << value.as(get()) << '"';
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return !value.as(get()).empty();
    }

    virtual Cell push(const Cell &target, const Cell &item) const override {
      auto s = target.as(get());
      s.push_back(item.as(Rune::get()));
      return Cell(get(), s);
    }
  };
}

#endif
