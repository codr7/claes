#ifndef CLAES_MACRO_HPP
#define CLAES_MACRO_HPP

#include "claes/error.hpp"

namespace claes {
  using namespace std;

  struct Env;
  struct Forms;
  struct VM;

  struct Macro {
    using Body = function<E (const Macro &macro,
			     VM &vm, 
			     Env &env, 
			     const Forms &args,
			     const Loc &loc)>;

    struct Imp {
      Body body;
      string name;

      Imp(const string &name, const Body &body): body(body), name(name) {}
    };

    shared_ptr<const Imp> imp;

    Macro(const string &name, const Body &body): 
      imp(make_shared<const Imp>(name, body)) {}

    E call(VM &vm, 
	   Env &env, 
	   const Forms &args,
	   const Loc &loc);
  };

  inline bool operator==(const Macro &left, const Macro &right) {
    return left.imp.get() == right.imp.get();
  }

  inline strong_ordering operator<=>(const Macro &left, const Macro &right) {
    return left.imp->name <=> right.imp->name;
  }

  inline ostream &operator <<(ostream &out, const Macro &macro) {
    out << "(Macro " << macro.imp->name << ')';
    return out;
  }
}

#endif
