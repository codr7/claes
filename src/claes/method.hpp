#ifndef CLAES_METHOD_HPP
#define CLAES_METHOD_HPP

#include "claes/error.hpp"

namespace claes {
  using namespace std;

  struct Stack;
  struct VM;

  struct Method {
    using Args = vector<string>;
    using Body = function<E (const Method &method,
			     VM &vm,
			     Stack &stack,
			     int arity,
			     bool recursive,
			     const Loc &loc)>;

    struct Imp {
      Args args;
      Body body;
      string name;

      Imp(const string &name, const Args &args, const Body &body): 
	args(args), body(body), name(name) {}
    };

    shared_ptr<const Imp> imp;
    
    Method(const string &name, const Args &args, const Body &body): 
      imp(make_shared<const Imp>(name, args, body)) {}

    size_t arity() const {
      return imp->args.size();
    }
    
    E call(VM &vm, Stack &stack, int arity, bool recursive, const Loc &loc) const;

    bool vararg() const {
      return !imp->args.empty() && imp->args.back().back() == '*';
    }
  };

  inline bool operator==(const Method &left, const Method &right) {
    return left.imp.get() == right.imp.get();
  }

  inline strong_ordering operator<=>(const Method &left, const Method &right) {
    return left.imp->name <=> right.imp->name;
  }

  inline ostream &operator<<(ostream &out, const Method &method) {
    out << "(Method " << method.imp->name << ')';
    return out;
  }
}

#endif
