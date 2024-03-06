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
    Cell(const TType<T> &type, const V &value): 
      type(type), value(static_cast<T::Value>(value)) {}

    template <typename T>
    Cell(const TType<T> &type, const T &&value): 
      type(type), value(std::move(value)) {}

    Cell(const Cell &source): 
      type(source.type), value(source.value) {}
    
    Cell(Cell &&source): 
      type(source.type), value(std::move(source.value)) {}

    const Cell &operator =(const Cell &source) {
      type = source.type;
      value = source.value;
      return *this;
    }

    template <typename T>
    typename T::Value &as(const TType<T> &type) { 
      return any_cast<typename T::Value &>(value); 
    }

    template <typename T>
    const typename T::Value &as(const TType<T> &type) const { 
      return any_cast<const typename T::Value &>(value); 
    }
    
    E call(VM &vm, Stack &stack, int arity, const Loc &loc) const {
      return type.call(*this, vm, stack, arity, loc);
    }

    Cell clone() const {
      return type.clone(*this);
    }

    void dump(ostream &out) const {
      type.dump(*this, out);
    }

    E emit_call(VM &vm, 
		Env &env, 
		const Forms &args,
		const Loc &loc) const {
      return type.emit_call(*this, vm, env, args, loc);
    }

    E emit_id(VM &vm, 
	      Env &env, 
	      Forms &args,
	      const Loc &loc) const {
      return type.emit_id(*this, vm, env, args, loc);
    }

    E emit_literal(VM &vm, 
		   Env &env, 
		   Forms &args,
		   const Loc &loc) const {
      return type.emit_literal(*this, vm, env, args, loc);
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
