#ifndef CLAES_TYPES_SYM_HPP
#define CLAES_TYPES_SYM_HPP

#include "claes/sym.hpp"
#include "claes/type.hpp"
#include "claes/types/string.hpp"
#include "claes/types/sym.hpp"

namespace claes::types {
  using namespace claes;

  struct Sym: Type::Imp {
    using Value = const claes::Sym *;
    
    static TType<Sym> get() {
      static TType<Sym> t("Sym");
      return t;
    }    

    Sym(const string &name): Type::Imp(name) {}

    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const claes::Loc &loc) const override;

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

    virtual E js(const Cell &value, 
		 ostream &out, 
		 const claes::Loc &loc) const override {
      out << Cell(types::String::get(), value.as(get())->name);
      return nullopt;
    }

    virtual void say(const Cell &value, ostream &out) const override {
      out << value.as(get())->name;
    }
  };
}

#endif
