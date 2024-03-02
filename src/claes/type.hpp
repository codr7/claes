#ifndef CLAES_TYPE_HPP
#define CLAES_TYPE_HPP

#include <string>

namespace claes {
  using namespace std;

  struct Cell;

  struct Type {
    struct Imp {
      string name;
      Imp(const string &name): name(name) {}
      virtual ~Imp() {}
      virtual Cell clone(const Cell &value) const;
      virtual void dump(const Cell &value, ostream &out) const = 0;      
      virtual bool eq(const Cell &left, const Cell &right) const = 0;

      virtual bool is_true(const Cell &value) const {
	return true;
      }
    };

    shared_ptr<const Imp> imp;

    template <typename T>
    Type(shared_ptr<const T> imp): imp(imp) {}

    Cell clone(const Cell &value) const;

    void dump(const Cell &value, ostream &out) const {
      imp->dump(value, out);
    }
    
    bool eq(const Cell &left, const Cell &right) const {
      return imp->eq(left, right);
    }

    bool is_true(const Cell &value) const {
      return imp->is_true(value);
    }
  };

  inline bool operator ==(const Type &left, const Type &right) {
    return left.imp.get() == right.imp.get();
  }

  template <typename T> 
  struct TType: Type {
    template <typename...Args>
    TType(const string &name, Args&&...args):
      Type(make_shared<const T>(name, std::forward<Args>(args)...)) {}
  };
}

#endif
