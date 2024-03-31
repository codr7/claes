#include <iostream>

#include "claes/cell.hpp"
#include "claes/js.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/string.hpp"
#include "claes/types/vector.hpp"

namespace claes::js {
  P parse_ws(istream &in, Loc &loc) {
    char c = 0;
    
    while (in.get(c)) {
      if (!isspace(c)) {
	in.unget();
	break;
      }
      
      loc.column++;
    }

    return P(nullopt, nullopt);
  }

  P parse_id(istream &in, Loc &loc) {
    const auto form_loc = loc;
    stringstream buffer;
    char c = 0;
    
    while (in.get(c)) {
      if (!isgraph(c) ||  
	  c == '[' || c == ']' || c == '{' || c == '}' || 
	  c == '"' || c == ':' || c == ',') {
	in.unget();
	break;
      }

      buffer << c;
      loc.column++;
    }

    if (!buffer.tellp()) {
      return P(nullopt, nullopt);
    }

    const auto id = buffer.str();

    if (id == "null") {
      return P(NIL(), nullopt);
    }

    if (id == "true") {
      return P(T(), nullopt);
    }

    if (id == "false") {
      return P(F(), nullopt);
    }

    return P(nullopt, Error(loc, "Unknown identifier: ", id));
  }

  P parse_i64(istream &in, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return P(nullopt, nullopt); 
    }

    in.unget();

    if (!isdigit(c)) {
      return P(nullopt, nullopt);
    }

    types::I64::Value v = 0;

    while (in.get(c)) {
      if (!isdigit(c)) {
	in.unget();
	break;
      }

      v = v * 10 + c - '0';
      loc.column++;
    }

    return P(Cell(types::I64::get(), v), nullopt);
  }

  P parse_string(istream &in, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return P(nullopt, nullopt); 
    }

    if (c != '"') {
      in.unget();
      return P(nullopt, nullopt);
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
      
      if (c == '\\') {
	loc.column++;

	if (!in.get(c)) {
	  return P(nullopt, Error(loc, "Invalid string escape"));
	}

	switch (c) {
	case '"':
	  break;
	case 'n':
	  c = '\n';
	  break;
	case 't':
	  c = '\t';
	  break;
	}
      }

      buffer << c;
      loc.column++;
    }

    if (c != '"') { 
      return P(nullopt, Error(loc, "Invalid string")); 
    }

    loc.column++;
    return P(Cell(types::String::get(), buffer.str()), nullopt);
  }
  
  P parse_vector(istream &in, Loc &loc) {
    char c = 0;

    if (!in.get(c)) { 
      return P(nullopt, nullopt); 
    }

    if (c != '[') {
      in.unget();
      return P(nullopt, nullopt);
    }

    loc.column++;
    types::Vector::Value result;

    for (;;) {
      parse_ws(in, loc);

      if (in.get(c)) {
	if (c == ']') { 
	  loc.column++;
	  break; 
	}
	
	in.unget();
      } else {
	break;
      }

      if (!result.empty() && c != ',') {
	return P(nullopt, Error(loc, "Invalid array literal: ", c));
      }
      
      if (c == ',') {
	loc.column++;
	in.get(c);
      }

      if (auto [v, e] = parse(in, loc); e) { 
	return P(nullopt, e);
      } else if (v) {
	result.push_back(*v);
      } else {
	return P(nullopt, Error(loc, "Invalid array literal"));
      }
    }

    return P(Cell(types::Vector::get(), result), nullopt);
  }

  P parse(istream &in, Loc &loc) {
    vector<function<P(istream &in, Loc &loc)>> parsers = {
      parse_ws, 

      parse_i64,
      parse_string,
      parse_vector,

      parse_id
    };

    for (const auto &p: parsers) {
      if (auto [v, e] = p(in, loc); v || e) {
	return P(v, e);
      }
    }
    
    return P(nullopt, nullopt);
  }
}
