#ifndef CLAES_READER_HPP
#define CLAES_READER_HPP

#include "claes/error.hpp"
#include "claes/form.hpp"

namespace claes {
  using namespace std;

  using ReadT = pair<bool, optional<Error>>;

  using Reader = function<ReadT (istream &in, 
				 Forms &out, 
				 Location &location)>;
  
  ReadT read_call(istream &in, Forms &out, Location &location);
  ReadT read_form(istream &in, Forms &out, Location &location);
  ReadT read_i64(istream &in, Forms &out, Location &location);
  ReadT read_id(istream &in, Forms &out, Location &location);
  ReadT read_string(istream &in, Forms &out, Location &location);
  ReadT read_ws(istream &in, Forms &out, Location &location);

  pair<int, optional<Error>> read_forms(istream &in, Forms &out, Location &location);
}

#endif
