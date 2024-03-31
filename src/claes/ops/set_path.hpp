#ifndef CLAES_OPS_SET_PATH_HPP
#define CLAES_OPS_SET_PATH_HPP

#include <filesystem>
#include "claes/cell.hpp"
#include "claes/common.hpp"
#include "claes/op.hpp"

namespace claes::ops {
  using namespace claes;
  namespace fs = filesystem;
  
  struct SetPath: Op::Imp {
    fs::path path;

    SetPath(const fs::path &path): Op::Imp(Op::Code::SET_PATH), path(path) {}
    
    virtual void trace(VM &vm, ostream &out) const override {
      out << "SetPath path: " << path;
    }
  };
}

#endif
