#include <vector>
#include "claes/alloc.hpp"
#include "claes/cell.hpp"
#include "claes/form.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/stack.hpp"
#include "claes/types/i64.hpp"

using namespace claes;
using namespace std;

void alloc_tests() {
  const auto MAX = 1000;
  Alloc<int, 64> a;
  vector<int *> ps;

  for (int i = 0; i < MAX; i++) {
    ps.push_back(a.acquire(i));
  }

  for (auto p: ps) {
    a.free(p);
  }
  
  ps.clear();

  for (int i = 0; i < MAX; i++) {
    ps.push_back(a.acquire(i));
  }
}

void form_tests() {
  Forms fs;
  Location l("form_tests");
  fs.push<forms::Id>(l, "foo");

  fs.push<forms::Literal>(l, Cell(types::i64, 42));
}

void stack_tests() {
  const auto MAX = 1000;
  Stack s;

  for (int i = 0; i < MAX; i++) {
    s.push(types::i64, i);
  }

  for (int i = 0; i < MAX; i++) {
    s.pop();
  }
}
  
int main() {  
  alloc_tests();
  form_tests();
  stack_tests();
  return 0;
}
