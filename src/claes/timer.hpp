#ifndef CLAES_TIMER_HPP
#define CLAES_TIMER_HPP

#include <chrono>

namespace claes {
  using namespace std;
  
  struct Timer {
    using Clock = chrono::steady_clock;
    using Time = Clock::time_point;

    Timer() { start = Clock::now(); }
    
    auto ms() { 
      return chrono::duration_cast<chrono::milliseconds>(Clock::now() - start).count();
    }

    Time start;
  };
}

#endif
