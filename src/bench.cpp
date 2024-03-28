#include <iostream>
#include "timer.hpp"

using namespace std;

int main() {
  Timer t;
  cout << t.ms() << endl;
  return 0;
}
