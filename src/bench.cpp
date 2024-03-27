#include <iostream>
#include <set>

#include "bset.hpp"
#include "bin_set.hpp"
#include "timer.hpp"

using namespace std;

static const auto REPS = 10;
static const auto BIN_SET_MAX = 10000;

static void bset() {
  BSet<int> s;

  for (auto i = 0; i < BIN_SET_MAX; i++) {
    assert(s.insert(i));
    assert(s.contains(i));
  }
}

static void bin_set() {
  BinSet<int> s;

  for (auto i = 0; i < BIN_SET_MAX; i++) {
    assert(s.insert(i));
    assert(s.contains(i));
  }
}

static void std_set() {
  set<int> s;

  for (auto i = 0; i < BIN_SET_MAX; i++) {
    auto [_, ok] = s.insert(i);
    assert(ok);
    assert(s.contains(i));
  }
}

int main() {
  Timer t;

  for (auto i = 0; i < REPS; i++) {
    bset();
  }

  cout << "BSet " << t.ms() << endl;
  t.reset();

  for (auto i = 0; i < REPS; i++) {
    bin_set();
  }

  cout << "BinSet " << t.ms() << endl;
  t.reset();

  for (auto i = 0; i < REPS; i++) {
    std_set();
  }

  cout << "std::set " << t.ms() << endl;
  return 0;
}
