#pragma once

#include <cassert>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

template <typename E>
struct BinSet {
  // At each index i, the vector is of either size 0 or 2^i, 
  // and contains elements in ascending order.
  
  vector<vector<E>> subs;
  size_t len;
  
  BinSet(): subs(), len(0) {}
  BinSet(const BinSet &other) = default;	
  BinSet(BinSet &&other) = default;
	
  const BinSet &operator=(BinSet other) {
    std::swap(subs, other.subs);
    std::swap(len, other.len);
    return *this;
  }
	
  bool empty() const {
    return len == 0;
  }
		
  void clear() {
    subs.clear();
    len = 0;
  }
	
  bool contains(const E &val) const {
    for (const auto &vals: subs) {
      for (size_t start = 0, end = vals.size(); start < end; ) {
	size_t mid = start + (end - start) / 2;
	const E &mv = vals[mid];
	
	if (val < mv) {
	  end = mid;
	} else if (val > mv) {
	  start = mid + 1;
	} else {
	  // val == mv
	  return true;
	}
      }
    }

    return false;
  }
	
  bool insert(E val) {
    if (contains(val)) {
      return false;
    }

    insert_unique(vector<E> {std::move(val)});
    return true;
  }
  	
  void insert_unique(vector<E> to_put) {
    assert(len < SIZE_MAX);

    for (size_t i = 0; ; i++) {
      if (i >= subs.size()) {
	subs.push_back(std::move(to_put));
	break;
      }

      vector<E> &vals = subs.at(i);

      if (vals.empty()) {
	vals = std::move(to_put);
	break;
      }
      
      // Merge
      assert(vals.size() == to_put.size());
      assert(vals.size() <= SIZE_MAX / 2);
      vector<E> next;
      next.reserve(vals.size() * 2);
      size_t j = 0;
      size_t k = 0;

      for (; j < vals.size() && k < to_put.size(); ) {
	if (vals[j] < to_put[k]) {
	  next.push_back(std::move(vals[j]));
	  j++;
	} else {
	  next.push_back(std::move(to_put[k]));
	  k++;
	}
      }

      for (; j < vals.size(); j++) {
	next.push_back(std::move(vals[j]));
      }

      for (; k < to_put.size(); k++) {
	next.push_back(std::move(to_put[k]));
      }

      vals.clear();
      vals.shrink_to_fit();
      to_put = std::move(next);
    }

    len++;
  }
  
  
  void check() const {
    size_t sum = 0;

    for (size_t i = 0; i < subs.size(); i++) {
      assert(i < numeric_limits<size_t>::digits);
      const vector<E> &vals = subs.at(i);
      size_t len = vals.size();
      assert(len == 0 || len == static_cast<size_t>(1) << i);

      for (size_t j = 1; j < len; j++) {
	assert(vals[j - 1] < vals[j]);
      }

      sum += len;
    }

    assert(sum == len);
  }
};
