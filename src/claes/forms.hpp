#ifndef CLAES_FORMS_HPP
#define CLAES_FORMS_HPP

#include <deque>
#include "claes/form.hpp"

namespace claes {
  struct Forms {
    using Items = deque<Form>;
    Items items;

    Items::iterator begin() {
      return items.begin();
    }

    Items::const_iterator begin() const {
      return items.begin();
    }

    void collect_ids(set<string> &out) const {
      for (const auto &f: items) {
	f.collect_ids(out);
      }
    }

    E emit(VM &vm, Env &env) {
      while (!empty()) {
	if (auto e = pop().emit(vm, env, *this); e) {
	  return e;
	}
      }

      return nullopt;
    }

    bool empty() const {
      return items.empty();
    }

    Items::iterator end() {
      return items.end();
    }

    Items::const_iterator end() const {
      return items.end();
    }

    size_t len() const {
      return items.size();
    }

    Form peek() const {
      return items.front();
    }
    
    Form pop() {
      auto f = peek();
      items.pop_front();
      return f;
    }

    Form pop_back() {
      auto f = items.back();
      items.pop_back();
      return f;
    }
    
    template <typename T, typename...Args>
    Form push(const Loc loc, Args&&...args) {
      return items.emplace_back(make_shared<T>(loc, std::forward<Args>(args)...));
    }
  };

  inline ostream &operator<<(ostream &out, const Forms &fs) {
    auto i = 0;

    for (const auto &f: fs.items) {
      if (i++) {
	out << ' ';
      }

      f.imp->dump(out);
    }

    return out;
  }
}

#endif
