#pragma once

#include "claes/map.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Map: Type::Imp {
    using Value = claes::Map;
    
    static TType<Map> get() {
      static TType<Map> t("Map");
      return t;
    }    

    Map(const string &name): Type::Imp(name) {}
    
    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const claes::Loc &loc) const override;

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   bool recursive,
		   const claes::Loc &loc) const override;

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override;

    virtual void dump(const Cell &value, ostream &out) const override;
    virtual bool eq(const Cell &left, const Cell &right) const override;
    virtual bool is_true(const Cell &value) const override;
    virtual Cell iter(const Cell &target) const override;

    virtual E js(const Cell &value, 
		 ostream &out, const 
		 claes::Loc &loc) const override;

    virtual void push(Cell &target, const Cell &item) const override;
  };
}

