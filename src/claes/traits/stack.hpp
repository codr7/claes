#ifndef CLAES_TRAITS_STACK_HPP
#define CLAES_TRAITS_STACK_HPP

namespace claes::traits {
  struct Stack {
    void push(Cell &target, const Cell &item) const;  
  };
}

#endif
