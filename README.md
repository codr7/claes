# Introduction
This project aims to implement a custom Lisp in C++.

## Setup
Launching the binary without arguments starts a REPL, `rlwrap` may be used to add support for line editing.

```
git clone https://github.com/codr7/claes.git
cd claes
mkdir build
cd build
cmake ..
make claes
rlwrap ./claes

claes v2
may the source be with you

  (say "hello" "world")

hello world
_
```

## Language
To me, Lisp is all about ergonomics.<br/>
<br/>
I've tried to capture some of the pragmatism of Common Lisp and combine it with good ideas from Scheme, Clojure, Perl, Python and Ruby; while taking the opportunity to scratch a couple of personal itches along the way.
