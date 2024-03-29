#pragma once

#include <chrono>

using namespace std;
using namespace chrono;

struct Timer {
  using Clock = steady_clock;
  using Time = Clock::time_point;

  Time start;

  Timer() { 
    reset();
  }
  
  int ms() const { 
    return duration_cast<milliseconds>(Clock::now() - start).count();
  }

  void reset() {
    start = Clock::now();
  }
};
