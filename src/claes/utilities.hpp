#ifndef CLAES_UTILITIES_HPP
#define CLAES_UTILITIES_HPP

#include <set>
#include <sstream>

namespace claes {
  using namespace std;
  
  template <typename Arg, typename...Args>
  string to_string(Arg &&arg, Args &&...args) {
    stringstream buf;
    buf << arg;
    ((buf << std::forward<Args>(args)), ...);
    return buf.str();
  }

  inline string replace_all(string s, const string &from, const string &to) {
    auto i = 0;

    while ((i = s.find(from, i)) != string::npos) {
      s.replace(i, from.length(), to);
      i += to.length(); 
    }
    
    return s;
  }

  template <typename T>
  ostream &operator << (ostream &out, const set<T> &set) {
    out << '[';
    
    for (auto i = set.begin(); i != set.end(); i++) {
      if (i != set.begin()) {
	out << ' ';
      }
      
      out << *i;
    }
    
    out << ']';
    return out;
  }
}

#endif
