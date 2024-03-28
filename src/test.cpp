#include <cassert>
#include <vector>

#include "f64.hpp"

#include "claes/alloc.hpp"
#include "claes/cell.hpp"
#include "claes/error.hpp"
#include "claes/form.hpp"
#include "claes/forms/call.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/ops/exit.hpp"
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

static void f64_init_tests() {
  const auto x = f64::make(2, 25);
  assert(f64::exp(x) == 2);
  assert(f64::val(x) == 25);
}

static void f64_arithmetic_tests() {
  assert(f64::add(f64::make(2, 75), f64::make(2, 25)) == f64::make(2, 100));
  assert(f64::sub(f64::make(2, 75), f64::make(2, 25)) == f64::make(2, 50));
  assert(f64::mul(f64::make(2, 25), f64::make(2, 200)) == f64::make(2, 50));
  assert(f64::div(f64::make(2, 50), f64::make(2, 200)) == f64::make(2, 25));
}

static void f64_trunc_frac_tests() {
  const auto x = f64::make(2, 725);
  assert(f64::trunc(x) == 7);
  assert(f64::frac(x) == 25);
}

void f64_tests() {
 f64_init_tests();
 f64_arithmetic_tests();
 f64_trunc_frac_tests();
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
  vm.emit<ops::Exit>();

  Stack s;
  vm.eval(0, s);
  assert(s.pop() == v);
  assert(vm.pc == 2);
}
  
int main() {  
  alloc_tests();
  f64_tests();
  form_tests();
  read_tests();
  stack_tests();
  vm_tests();
  return 0;
}
