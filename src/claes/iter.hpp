#ifndef CLAES_ITER_HPP
#define CLAES_ITER_HPP

#include "claes/cell.hpp"

namespace claes {
  struct Iter {
    using Result = pair<optional<Cell>, E>;

    struct Imp {
      virtual ~Imp() {}
      virtual Result next() = 0;
      virtual Imp *clone() const = 0;
      
      virtual strong_ordering compare(const Iter &other) const {
	return this <=> other.imp.get();    
      }

      virtual void dump(ostream &out) const {
	out << this;
      }

      virtual bool eq(const Iter &other) const {
	return this == other.imp.get();
      }
    };

    unique_ptr<Imp> imp;

    Iter(Imp *imp): imp(imp) {}
    Iter(const Iter &source): imp(source.imp->clone()) {}

    Result next() {
      return imp->next();
    }

    strong_ordering compare(const Iter &other) const {
      return imp->compare(other);
    }

    void dump(ostream &out) const {
      imp->dump(out);
    }

    bool eq(const Iter &other) const {
      return imp->eq(other);
    }
  };

  inline bool operator==(const Iter &left, const Iter &right) {
    return left.eq(right);
  }

  inline strong_ordering operator<=>(const Iter &left, const Iter &right) {
    return left.compare(right);
  }

  inline ostream &operator<<(ostream &out, const Iter &i) {
    out << "(Iter ";
    i.dump(out);
    out << ')';
    return out;
  }
}

#endif
