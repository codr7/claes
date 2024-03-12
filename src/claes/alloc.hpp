#ifndef CLAES_ALLOC_HPP
#define CLAES_ALLOC_HPP

#include <deque>
#include <memory>
#include <vector>

namespace claes {
  using namespace std;
  
  // T is the kind of object to be allocated, N the slab size
  template <typename T, size_t N>
  struct Alloc {
    //A slab is a properly aligned chunk of memory with space for N objects
    using Slab = array<typename aligned_storage<sizeof(T), alignof(T)>::type, N>; 
    
    Slab &push_slab() {
      n = 0;
      return slabs.emplace_back();
    }

    // Returns an initialized object
    template <typename...Args>
    T *get(Args&&...args) {
      auto *s = get_slot();
      *s = T(std::forward<Args>(args)...);
      return s;
    }

    // Returns a pointer to the next available slot
    T *get_slot() {
      if (!free_slots.empty()) {
	auto s = free_slots.back();
	free_slots.pop_back();
	return s;
      }

      Slab &s = (slabs.empty() || n == N) ? push_slab() : slabs.back();
      return reinterpret_cast<T *>(&s[n++]);
    }

    void free(T *pointer) {
      free_slots.push_back(pointer);
    }

    // Using deque instead of vector here since we need stable pointers
    deque<Slab> slabs;
    vector<T *> free_slots;

    // Number of used slots in currently active slab
    size_t n = 0;
  };
}

#endif
