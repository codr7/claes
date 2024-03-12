#include <cassert>
#include <vector>

#include "claes/alloc.hpp"
#include "claes/cell.hpp"
#include "claes/error.hpp"
#include "claes/form.hpp"
#include "claes/forms/call.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/ops/push.hpp"
#include "claes/ops/stop.hpp"
#include "claes/read.hpp"
#include "claes/stack.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/string.hpp"
#include "claes/vm.hpp"

using namespace claes;
using namespace std;

void alloc_tests() {
  const auto MAX = 1000;
  Alloc<int, 64> a;
  vector<int *> ps;

  for (int i = 0; i < MAX; i++) {
    ps.push_back(a.get(i));
  }

  for (auto p: ps) {
    a.free(p);
  }
  
  ps.clear();

  for (int i = 0; i < MAX; i++) {
    ps.push_back(a.get(i));
  }
}

void form_tests() {
  Forms fs;
  Loc l("form_tests");
  fs.push<forms::Id>(l, "foo");
  fs.push<forms::Literal>(l, Cell(types::I64::get(), 42));
}

void read_tests() {
  Forms fs;
  stringstream in("foo 42 (foo \"bar\")");
  Loc loc("read_tests");

  auto [n, e] = read_forms(in, fs, loc);
  assert(!e);
  assert(n == 3);
  
  const auto id_form = fs.pop();
  assert(id_form.as<forms::Id>()->name == "foo");

  const auto literal_form = fs.pop();
  assert(literal_form.as<forms::Literal>()->value.as(types::I64::get()) == 42);

  const auto call_form = fs.pop();
  const auto call = call_form.as<forms::Call>();
  const auto target = call->target.as<forms::Id>();
  assert(target->name == "foo");
  const auto arg = call->args.peek().as<forms::Literal>();
  assert(arg->value.as(types::String::get()) == "bar");
}

void stack_tests() {
  const auto MAX = 1000;
  Stack s;

  for (int i = 0; i < MAX; i++) {
    s.push(types::I64::get(), i);
  }

  for (int i = 0; i < MAX; i++) {
    s.pop();
  }
}

void vm_tests() {
  const Cell v(types::I64::get(), 42);

  VM vm;
  vm.emit<ops::Push>(v);
  vm.emit<ops::Stop>();

  Stack s;
  vm.eval(0, s);
  assert(s.pop() == v);
  assert(vm.pc == 2);
}
  
int main() {  
  alloc_tests();
  form_tests();
  read_tests();
  stack_tests();
  vm_tests();
  return 0;
}
