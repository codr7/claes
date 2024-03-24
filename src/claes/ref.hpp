#ifndef CLAES_REF_HPP
#define CLAES_REF_HPP

#include "claes/cell.hpp"

namespace claes {
  struct Ref {
    struct Imp {
      Cell value;
      int ref_count = 1;

      Imp(const Cell &value): value(value) {}
      
      void deref() {
	if (!--ref_count) {
	  delete this;
	}
      }
    };

    Imp *imp;

    Ref(const Cell &value): imp(new Imp(value)) {}
    
    Ref(const Ref &source): imp(source.imp) {
      imp->ref_count++;
    }

    ~Ref() {
      imp->deref();
    }
    
    const Ref &operator=(const Ref &source) {
      imp->deref();
      imp = source.imp;
      imp->ref_count++;
      return *this;
    }
  };

  inline bool operator==(const Ref &left, const Ref &right) {
    return left.imp->value == right.imp->value;    
  }
  
  inline strong_ordering operator<=>(const Ref &left, const Ref &right) {
    return left.imp->value <=> right.imp->value;
  }
  
  inline ostream &operator<<(ostream &out, const Ref &r) {
    out << '&' << r.imp->value;
    return out;
  }
}

#endif
