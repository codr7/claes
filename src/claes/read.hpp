#ifndef CLAES_READER_HPP
#define CLAES_READER_HPP

#include <functional>

#include "claes/error.hpp"
#include "claes/form.hpp"

namespace claes {
  using namespace std;

  using ReadT = pair<bool, E>;

  using Reader = function<ReadT (istream &in, 
				 Forms &out, 
				 Loc &loc)>;
  
  ReadT read_call(istream &in, Forms &out, Loc &loc);
  ReadT read_f64(istream &in, Forms &out, Loc &loc);
  ReadT read_form(istream &in, Forms &out, Loc &loc);
  ReadT read_i64(istream &in, Forms &out, Loc &loc);
  ReadT read_id(istream &in, Forms &out, Loc &loc);
  ReadT read_map(istream &in, Forms &out, Loc &loc);
  ReadT read_pair(istream &in, Forms &out, Loc &loc);
  ReadT read_quote(istream &in, Forms &out, Loc &loc);
  ReadT read_ref(istream &in, Forms &out, Loc &loc);
  ReadT read_rune(istream &in, Forms &out, Loc &loc);
  ReadT read_splat(istream &in, Forms &out, Loc &loc);
  ReadT read_string(istream &in, Forms &out, Loc &loc);
  ReadT read_unquote(istream &in, Forms &out, Loc &loc);
  ReadT read_vector(istream &in, Forms &out, Loc &loc);
  ReadT read_ws(istream &in, Forms &out, Loc &loc);

  pair<int, E> read_forms(istream &in, Forms &out, Loc &loc);
}

#endif
