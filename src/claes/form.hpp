#ifndef CLAES_FORM_HPP
#define CLAES_FORM_HPP

#include <deque>
#include "claes/location.hpp"

namespace claes {
  struct Form {
    template <typename T, typename...Args>
    static Form make(const Location &location, Args&&...args) {
      return Form(make_shared<T>(location, std::forward<Args>(args)...));
    };
      
    struct Imp {
      Location location;
      Imp(const Location &location): location(location) {}
    };

    shared_ptr<const Imp> imp;
    Form(shared_ptr<const Imp> imp): imp(imp) {}

    template <typename T>
    const T &as() const { 
      return *static_cast<const T *>(imp.get()); 
    }
  };

  struct Forms {
    deque<Form> items;
    
    Form peek() const {
      return items.front();
    }
    
    Form pop() {
      auto f = peek();
      items.pop_front();
      return f;
    }
    
    template <typename T, typename...Args>
    Form push(const Location location, Args&&...args) {
      return items.emplace_back(make_shared<T>(location, std::forward<Args>(args)...));
    }
  };
}

#endif
