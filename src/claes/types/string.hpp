#ifndef CLAES_TYPES_STRING_HPP
#define CLAES_TYPES_STRING_HPP

#include "claes/stack.hpp"
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

    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const claes::Loc &loc) const override {
      stringstream buffer;

      struct Rec {
	static void call(int arity, Stack &stack, ostream &out) {
	  if (arity) {
	    const auto v = stack.pop();
	    call(arity-1, stack, out);
	    v.say(out);
	  } else {
	    stack.peek().say(out);
	  }
	}
      };
      
      Rec::call(arity-1, stack, buffer);
      stack.peek() = Cell(get(), buffer.str());
      return nullopt;
    }

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      auto s = value.as(get());
      s = replace_all(s, "\"", "\\\"");
      s = replace_all(s, "\n", "\\n");
      s = replace_all(s, "\t", "\\t");
      out << '"' << s << '"';
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return !value.as(get()).empty();
    }

    virtual Cell iter(const Cell &target) const override;

    virtual E js(const Cell &value, 
		 ostream &out, 
		 const claes::Loc &loc) const override {
      dump(value, out);
      return nullopt;
    }

    virtual void push(Cell &target, const Cell &item) const override {
      target.as(get()).push_back(item.as(Rune::get()));
    }

    virtual void say(const Cell &value, ostream &out) const override {
      out << value.as(get());
    }
  };
}

#endif
