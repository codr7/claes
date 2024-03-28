#pragma once

#include <cassert>
#include <vector>

using namespace std;

template <typename T>
struct BSet {
  using Items = vector<T>;
  using iterator = Items::iterator;
  Items items;
  
  bool contains(const T &item) const {
    const auto [_, ok] = find(item);
    return ok;
  }

  bool insert(T item) {
    auto [i, ok] = find(item);

    if (ok) {
      return false;
    }

    if (items.empty() || i == items.size()) {
      items.push_back(std::move(item));
    } else {
      items.push_back(T{});
      auto j = items.begin() + i, k = items.end()-1;
      move(j, k, j+1);
      *j = std::move(item);
    }

    return true;
  }

  pair<size_t, bool> find(const T &item) const {
    auto i = 0;
    auto j = items.size();

    while (i < j) {
      auto k = i + (j - i) / 2;
      const auto &ik = items[k];

      if (item < ik) {
	j = k;
      } else if (item > ik) {
	i = k + 1;
      } else {
	return make_pair(k, true);
      }
    }

    return make_pair(i, false);
  }
};

template <typename T>
ostream &operator <<(ostream &out, const BSet<T> &s) {
  out << '[';
  auto i = 0;

  for (auto item: s.items) {
    if (i++) {
      out << ' ';
    }

    out << item;
  }
  
  out << ']';
  return out;
}
