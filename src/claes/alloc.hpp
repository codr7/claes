#ifndef CLAES_ALLOC_HPP
#define CLAES_ALLOC_HPP

#include <deque>
#include <memory>
#include <vector>

namespace claes {
  using namespace std;
  
  template <typename T, size_t N>
  struct Alloc {
    struct Slab { typename aligned_storage<sizeof(T), alignof(T)>::type slots[N]; };
    
    Slab &push_slab() {
      n = 0;
      return slabs.emplace_back();
    }

    T *acquire() {
      if (!free_slots.empty()) {
	auto s = free_slots.back();
	free_slots.pop_back();
	return s;
      }

      Slab &s = (slabs.empty() || n == N) ? push_slab() : slabs.back();
      return reinterpret_cast<T *>(&s.slots[n++]);
    }

    template <typename...Args>
    T *acquire(Args&&...args) {
      auto *s = acquire();
      *s = T(std::forward<Args>(args)...);
      return s;
    }

    void free(T *pointer) {
      free_slots.push_back(pointer);
    }

    deque<Slab> slabs;
    vector<T *> free_slots;
    size_t n = 0;
  };
}

#endif
