#include <iostream>

#include "claes/iters/map_items.hpp"
#include "claes/stack.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/map.hpp"
#include "claes/types/pair.hpp"
#include "claes/types/string.hpp"
#include "claes/types/sym.hpp"

namespace claes::types {
  E Map::call(VM &vm, 
	      Stack &stack, 
	      int arity,
	      const claes::Loc &loc) const {
    Value result;
    
    while (arity--) {
      claes::push(result, stack.pop());
    }

    stack.push(get(), result);
    return nullopt;
  }

  E Map::call(Cell &target, 
	      VM &vm, 
	      Stack &stack, 
	      int arity,
	      bool recursive,
	      const claes::Loc &loc) const {
    if (!arity) {
      return Error(loc, "Not enough arguments");
    }

    if (arity > 2) {
      return Error(loc, "Invalid map call");
    }
    
    auto &m = target.as(get());
    optional<Cell> v;

    if (arity == 2) {
      v = stack.pop();
    }

    auto k = stack.pop();

    if (k.type == Pair::get()) {
      const auto p = k.as(Pair::get());
      k = p.first;
      v = p.second;
    }

    auto found = m.find(k);

    if (arity == 2 || v) {
      if (found != m.end()) {
	m.erase(found);
      }

      m.insert(make_pair(k, *v));
    } else {
      if (found == m.end()) {
	stack.push(NIL());
      } else {
	stack.push(found->second);
      }
    }

    return nullopt;
  }

  strong_ordering Map::compare(const Cell &left, 
				  const Cell &right) const {
    auto lvs = left.as(get()), rvs = right.as(get());

    for (const auto &li = lvs.begin(), 
	   &ri = rvs.begin();;) {
      if (li == lvs.end()) {
	return strong_ordering::less;
      }

      if (ri == rvs.end()) {
	return strong_ordering::greater;
      }

      auto lv = li->first, rv = ri->first;

      if (const auto r = lv <=> rv; r != strong_ordering::equal) {
	return r;
      }
    }

    return strong_ordering::equal;
  }

  void Map::dump(const Cell &value, ostream &out) const {
    out << '{';
      
    auto i = 0;
    for (const auto &it: value.as(get())) {
      if (i++ > 0) {
	out << ' ';
      }

      out << it.first;
      
      if (it.first != it.second) {
	out << ':' << it.second;
      }
    }

    out << '}';
  }

  bool Map::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
    
  Cell Map::iter(const Cell &target) const {
    return Cell(Iter::get(), iters::MapItems::make(target.as(get())));
  }

  bool Map::is_true(const Cell &value) const {
    return !value.as(get()).empty();
  }

  E Map::js(const Cell &value, ostream &out, const claes::Loc &loc) const {
    out << '{';
    auto i = 0;
      
    for (const auto &it: value.as(get())) {
      if (i++ > 0) {
	out << ", ";
      }

      const auto &k = it.first, &v = it.second;

      if (k.type != Sym::get() && k.type != String::get()) {
	return Error(loc, "Invalid js object key: ", k);
      }

      if (const auto e = k.js(out, loc); e) {
	return e;
      }
      
      out << ": ";

      if (const auto e = v.js(out, loc); e) {
	return e;
      }      
    }
      
    out << '}';
    return nullopt;
  }

  void Map::push(Cell &target, const Cell &item) const {
    claes::push(target.as(get()), item);
  }
}
