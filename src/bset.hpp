#pragma once

#include <vector>

using namespace std;

template <typename T>
struct BSet {
  using Items = vector<T>;
  Items items;

  bool contains(const T &item) const {
    const auto [_, ok] = find_index(item);
    return ok;
  }

  bool insert(T item) {
    const auto [i, ok] = find_index(item);

    if (ok) {
      return false;
    }

    if (items.empty()) {
      items.push_back(item);
    } else {
      items.push_back(std::move(items.back()));
      auto pos = items.begin() + i;
      move(pos, items.end()-1, pos+1);
      *pos = item;
    }

    return true;
  }

  pair<int, bool> find_index(const T &item) const {
    auto i = 0;
    auto j = items.size();

    while (i < j) {
      const auto k = i + (j - i) / 2;
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
