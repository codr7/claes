#ifndef CLAES_VECTOR_HPP
#define CLAES_VECTOR_HPP

#include <vector>
#include "claes/cell.hpp"

namespace claes {
  struct Vector {
    struct Imp {
      vector<Cell> items;
      int ref_count = 1;

      void deref() {
	if (!--ref_count) {
	  delete this;
	}
      }
    };

    Imp *imp;
    Vector(): imp(new Imp()) {}
    
    Vector(const Vector &source): imp(source.imp) {
      imp->ref_count++;
    }

    ~Vector() {
      imp->deref();
    }
    
    const Vector &operator=(const Vector &source) {
      imp->deref();
      imp = source.imp;
      imp->ref_count++;
      return *this;
    }
  };
}

#endif
