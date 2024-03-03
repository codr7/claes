#include <sstream>

#include "claes/env.hpp"
#include "claes/form.hpp"
#include "claes/libraries/core.hpp"
#include "claes/read.hpp"
#include "claes/ops/stop.hpp"
#include "claes/stack.hpp"
#include "claes/vm.hpp"

namespace claes {
  void VM::repl(istream &in, ostream &out) {
    stringstream buffer;
    Stack stack;
    Env env;
    libraries::Core core;
    env.import_from(core);

    for (;;) {
      out << "  ";
     
      string line;
      if (!getline(in, line)) { break; }
       
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

	emit<ops::Stop>();

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
