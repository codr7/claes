#include "claes/map.hpp"
#include "claes/types/pair.hpp"

namespace claes {
  bool push(Map &map, const Cell &item) {
    Cell k = item, v = k;
      
    if (item.type == types::Pair::get()) {
      const auto &p = item.as(types::Pair::get());
      k = p.first;
      v = p.second;
    }

    const auto [_, ok] = map.insert(make_pair(k, v));
    return ok;
  }
}
