#ifndef CLAES_EXPR_HPP
#define CLAES_EXPR_HPP

#include "claes/env.hpp"
#include "claes/form.hpp"
#include "claes/common.hpp"

namespace claes {
  struct Expr {
    Env env;
    Form form;
    optional<PC> pc;

    Expr(const Form &form, const Env &env):
      env(env.imp, form.collect_ids()), form(form) {}
  };

  inline bool operator==(const Expr &left, const Expr &right) {
    stringstream ls, rs;
    ls << left.form;
    rs << right.form;
    return ls.str() == rs.str();
  }

  inline strong_ordering operator<=>(const Expr &left, const Expr &right) {
    stringstream ls, rs;
    ls << left.form;
    rs << right.form;
    return ls.str() <=> rs.str();
  }

  inline ostream &operator<<(ostream &out, const Expr &e) {
    out << "(Expr " << e.form << ')';
    return out;
  }
}

#endif
