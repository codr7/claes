#include <sstream>

#include "claes/env.hpp"
#include "claes/form.hpp"
#include "claes/forms.hpp"
#include "claes/libs/core.hpp"
#include "claes/read.hpp"
#include "claes/ops/exit.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

namespace claes {
  void VM::repl(istream &in, ostream &out, Env &env) {
    out << "claes v" << VERSION << endl;
    out << "may the source be with you" << endl << endl;

    stringstream buffer;
    Stack stack;

    for (;;) {
      out << "  ";
     
      string line;
      
      if (!getline(in, line)) { 
	break; 
      }
       
      if (line.empty()) {
	Loc loc("repl", 1, 1);
	PC start_pc = emit_pc();
	Forms fs;
	buffer.seekp(0);
	

	if (auto [_, e] = read_forms(buffer, fs, loc); e) {
	  out << *e << endl;
	  buffer.str("");
	  buffer.clear();
	  continue;
	}

	buffer.str("");
	buffer.clear();

	if (auto e = fs.emit(*this, env); e) {
	  out << *e << endl;
	  continue;
	}

	emit<ops::Exit>();

	if (auto e = eval(start_pc, stack); e) {
	  out << *e << endl;
	  break;
	}

	if (stack.empty()) {
	  out << '_' << endl;
	} else {
	  out << stack.pop() << endl;
	}
      } else {
	buffer << line << endl;
      }
    }
  }
}
