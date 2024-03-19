#ifndef CLAES_ITER_HPP
#define CLAES_ITER_HPP

namespace claes {
  struct Iter {
    using Result = pair<optional<Cell>, E>;

    struct Imp {
      int ref_count = 1;

      virtual ~Imp() {}
      virtual Result next() = 0;
      
      virtual strong_ordering compare(const Iter &other) const {
	return this <=> other.imp;    
      }

      void deref() {
	if (!--ref_count) {
	  delete this;
	}
      }

      virtual void dump(ostream &out) const = 0;

      virtual bool eq(const Iter &other) const {
	return this == other.imp;
      }
    };

    Imp *imp;

    Iter(Imp *imp): imp(imp) {}

    Iter(const Iter &source): imp(source.imp) {
      imp->ref_count++;
    }

    ~Iter() {
      imp->deref();
    }
    
    const Iter &operator=(const Iter &source) {
      imp->deref();
      imp = source.imp;
      imp->ref_count++;
      return *this;
    }

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
