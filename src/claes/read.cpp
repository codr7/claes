#include <map>

#include "claes/forms/call.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/read.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/string.hpp"

namespace claes {
  ReadT read_call(istream &in, Forms &out, Location &location) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '(') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_location = location;
    location.column++;
    Forms arguments;
    
    for (;;) {
      read_ws(in, out, location);

      if (in.get(c)) {
	if (c == ')') { 
	  break; 
	}

	in.unget();
      } else {
	break;
      }
      
      if (auto [f, e] = read_form(in, arguments, location); e) { 
	return ReadT(false, e); 
      } else if (!f) {
	break;
      }
    }

    if (c != ')') { 
      return ReadT(false, Error(location, "Syntax errror")); 
    }

    location.column++;
    const auto target = arguments.pop();
    out.push<forms::Call>(form_location, target, arguments);
    return ReadT(true, nullopt);
  }

  ReadT read_form(istream &in, Forms &out, Location &location) {
    const vector<Reader> readers {
      read_ws, 
      read_i64, 
      read_string, 
      read_call, 
      read_id
    };
    
    for (Reader r: readers) {
      if (auto [ok, e] = r(in, out, location); ok || e) {
	return ReadT(ok, e);
      } 
    }
    
    return ReadT(false, nullopt);
  }

  static pair<types::I64::Value, E> 
  read_i64(istream &in, Location &location, uint16_t base) {    
    static const map<char, int8_t> char_values = {
      {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
      {'8', 8}, {'9', 9}, {'a', 10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14},
      {'f', 15}
    };
    
    types::I64::Value v = 0;
    auto ci(char_values.end());
    char c = 0;
    
    while (in.get(c)) {
      if ((ci = char_values.find(c)) == char_values.end()) { break; }
      auto cv(ci->second);
      if (cv >= base) { return make_pair(0, Error(location, "Invalid integer: ", c)); }
      v = v * base + cv;
      location.column++;
    }
    
    if (!in.eof()) { in.unget();}
    return make_pair(v, nullopt);
  }

  ReadT read_i64(istream &in, Forms &out, Location &location) {
    char c = 0;
    if (!in.get(c)) { return ReadT(false, nullopt); }
    if (c) { in.unget(); }
    if (!isdigit(c)) { return ReadT(false, nullopt); }
    const auto form_location = location;
    auto [v, e] = read_i64(in, location, 10);
    if (e) { return ReadT(false, e); }
    out.push<forms::Literal>(form_location, Cell(types::I64::get(), v));
    return ReadT(true, nullopt);
  }

  ReadT read_id(istream &in, Forms &out, Location &location) {
    const auto form_location = location;
    stringstream buffer;
    char c = 0;
    
    while (in.get(c)) {
      if (!isgraph(c) ||  c == '(' || c == ')') {
	in.unget();
	break;
      }

      buffer << c;
      location.column++;
    }

    if (!buffer.tellp()) {
      return ReadT(false, nullopt);
    }
    
    out.push<forms::Id>(form_location, buffer.str());
    return ReadT(true, nullopt);
  }

  ReadT read_string(istream &in, Forms &out, Location &location) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '"') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_location = location;
    location.column++;
    stringstream buffer;
    
    for (;;) {
      if (in.get(c)) {
	if (c == '"') { 
	  break; 
	}
      } else {
	break;
      }
      
      buffer << c;
    }

    if (c != '"') { 
      return ReadT(false, Error(location, "Invalid string")); 
    }

    location.column++;
    out.push<forms::Literal>(form_location, Cell(types::String::get(), buffer.str()));
    return ReadT(true, nullopt);
  }

  ReadT read_ws(istream &in, Forms &out, Location &location) {
    char c = 0;
    
    while (in.get(c)) {
      if (!isspace(c)) {
	in.unget();
	break;
      }
	  
      switch (c) {
      case ' ':
      case '\t':
	location.column++;
	break;
      case '\n':
	location.line++;
	location.column = 1;
	break;
      };
    }

    return ReadT(false, nullopt);
  }

  pair<int, E> read_forms(istream &in, Forms &out, Location &location) {
    auto n = 0;

    for (;; n++) {
      auto [ok, e] = read_form(in, out, location);
      
      if (e) {
	return make_pair(n, e);
      }

      if (!ok) {
	break;
      }
    }
    
    return make_pair(n, nullopt);
  }
}
