#include <iostream>
#include <map>

#include "claes/forms/call.hpp"
#include "claes/forms/id.hpp"
#include "claes/forms/literal.hpp"
#include "claes/forms/pair.hpp"
#include "claes/forms/quote.hpp"
#include "claes/forms/ref.hpp"
#include "claes/forms/vector.hpp"
#include "claes/read.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/string.hpp"

namespace claes {
  ReadT read_call(istream &in, Forms &out, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '(') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_loc = loc;
    loc.column++;
    Forms args;
    
    for (;;) {
      read_ws(in, out, loc);

      if (in.get(c)) {
	if (c == ')') { 
	  break; 
	}

	in.unget();
      } else {
	break;
      }
      
      if (auto [f, e] = read_form(in, args, loc); e) { 
	return ReadT(false, e); 
      } else if (!f) {
	break;
      }
    }

    if (c != ')') { 
      return ReadT(false, Error(loc, "Unexpected end of call: ", c)); 
    }

    loc.column++;
    const auto target = args.pop();
    out.push<forms::Call>(form_loc, target, args);
    return ReadT(true, nullopt);
  }

  ReadT read_form(istream &in, Forms &out, Loc &loc) {
    const vector<Reader> readers {
      read_ws, 

      read_call,
      read_i64, 
      read_pair,
      read_quote,
      read_ref,
      read_rune,
      read_string,
      read_vector,

      read_id
    };
    
    for (Reader r: readers) {
      if (auto [ok, e] = r(in, out, loc); ok || e) {
	return ReadT(ok, e);
      } 
    }
    
    return ReadT(false, nullopt);
  }

  static pair<types::I64::Value, E> 
  read_i64(istream &in, Loc &loc, uint16_t base) {    
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
      if (cv >= base) { return make_pair(0, Error(loc, "Invalid integer: ", c)); }
      v = v * base + cv;
      loc.column++;
    }
    
    if (!in.eof()) { in.unget();}
    return make_pair(v, nullopt);
  }

  ReadT read_i64(istream &in, Forms &out, Loc &loc) {
    char c = 0;
    if (!in.get(c)) { return ReadT(false, nullopt); }
    if (c) { in.unget(); }
    if (!isdigit(c)) { return ReadT(false, nullopt); }
    const auto form_loc = loc;
    auto [v, e] = read_i64(in, loc, 10);
    if (e) { return ReadT(false, e); }
    out.push<forms::Literal>(form_loc, Cell(types::I64::get(), v));
    return ReadT(true, nullopt);
  }

  ReadT read_id(istream &in, Forms &out, Loc &loc) {
    const auto form_loc = loc;
    stringstream buffer;
    char c = 0;
    
    while (in.get(c)) {
      if (!isgraph(c) ||  
	  c == '(' || c == ')' || c == '[' || c == ']' || c == '\\' || c == '"' || 
	  c == ':' || c == '&' || c == '\'') {
	in.unget();
	break;
      }

      buffer << c;
      loc.column++;
    }

    if (!buffer.tellp()) {
      return ReadT(false, nullopt);
    }
    
    out.push<forms::Id>(form_loc, buffer.str());
    return ReadT(true, nullopt);
  }

  ReadT read_pair(istream &in, Forms &out, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != ':') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_loc = loc;
    loc.column++;
    auto left = out.pop_back();
    read_ws(in, out, loc);

    if (auto ok = read_form(in, out, loc); ok.second) {
      return ok;
    } else if (!ok.first) {
      return ReadT(false, Error(loc, "Missing right part of pair"));
    }

    const auto right = out.pop_back();

    out.push<forms::Pair>(form_loc,
			  left,
			  left.as<forms::Quote>()
			  ? forms::Quote::make(right.imp->loc, right)
			  : right);
    
    read_ws(in, out, loc);

    if (in.get(c)) { 
      in.unget();

      if (c == ':') {
	if (auto ok = read_pair(in, out, loc); ok.second) {
	  return make_pair(false, ok.second);
	}
      }
    }

    return ReadT(true, nullopt);
  }

  ReadT read_quote(istream &in, Forms &out, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '\'') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_loc = loc;
    loc.column++;

    if (auto ok = read_form(in, out, loc); ok.second) {
      return ok;
    } else if (!ok.first) {
      return ReadT(false, Error(loc, "Invalid quote"));
    }

    out.push<forms::Quote>(form_loc, out.pop_back());
    return ReadT(true, nullopt);
  }

  ReadT read_ref(istream &in, Forms &out, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '&') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_loc = loc;
    loc.column++;

    if (auto ok = read_form(in, out, loc); ok.second) {
      return ok;
    } else if (!ok.first) {
      return ReadT(false, Error(loc, "Invalid reference"));
    }

    out.push<forms::Ref>(form_loc, out.pop_back());
    return ReadT(true, nullopt);
  }

  ReadT read_rune(istream &in, Forms &out, Loc &loc) {
    const auto form_loc = loc;
    char c = 0;
    
    if (!in.get(c)) {
      return ReadT(false, nullopt);
    }
    
    if (c != '\\') {
      in.unget();
      return ReadT(false, nullopt);
    }
  
    loc.column++;
    
    if (!in.get(c)) {
      return ReadT(false, Error(form_loc, "Invalid rune literal"));
    }
  
    loc.column++;
    out.push<forms::Literal>(form_loc, Cell(types::Rune::get(), c));
    return ReadT(true, nullopt);
  }

  ReadT read_string(istream &in, Forms &out, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '"') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_loc = loc;
    loc.column++;
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
      return ReadT(false, Error(loc, "Invalid string")); 
    }

    loc.column++;
    out.push<forms::Literal>(form_loc, Cell(types::String::get(), buffer.str()));
    return ReadT(true, nullopt);
  }

  ReadT read_vector(istream &in, Forms &out, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return ReadT(false, nullopt); 
    }

    if (c != '[') {
      in.unget();
      return ReadT(false, nullopt);
    }

    const auto form_loc = loc;
    loc.column++;
    Forms items;
    
    for (;;) {
      read_ws(in, out, loc);

      if (in.get(c)) {
	if (c == ']') { 
	  break; 
	}

	in.unget();
      } else {
	break;
      }
      
      if (auto [f, e] = read_form(in, items, loc); e) { 
	return ReadT(false, e); 
      } else if (!f) {
	break;
      }
    }

    if (c != ']') { 
      return ReadT(false, Error(loc, "Unexpected end of vector: ", c)); 
    }

    loc.column++;
    out.push<forms::Vector>(form_loc, items);
    return ReadT(true, nullopt);
  }

  ReadT read_ws(istream &in, Forms &out, Loc &loc) {
    char c = 0;
    
    while (in.get(c)) {
      if (!isspace(c)) {
	in.unget();
	break;
      }
	  
      switch (c) {
      case ' ':
      case '\t':
	loc.column++;
	break;
      case '\n':
	loc.line++;
	loc.column = 1;
	break;
      };
    }

    return ReadT(false, nullopt);
  }

  pair<int, E> read_forms(istream &in, Forms &out, Loc &loc) {
    auto n = 0;

    for (;; n++) {
      auto [ok, e] = read_form(in, out, loc);
      
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
