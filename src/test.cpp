#include <vector>
#include "claes/alloc.hpp"
#include "claes/stack.hpp"

using namespace std;

void alloc_tests() {
  const auto MAX = 1000;
  claes::Alloc<int, 64> a;
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

void stack_tests() {
  const auto MAX = 1000;
  claes::TType<int> t("Int");
  claes::Stack s;

  for (int i = 0; i < MAX; i++) {
    s.push(t, i);
  }

  for (int i = 0; i < MAX; i++) {
    s.pop();
  }
}
  
int main() {  
  alloc_tests();
  stack_tests();
  return 0;
}
