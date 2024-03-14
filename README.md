# introduction
This project aims to implement a custom Lisp in C++.

## setup
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

## language
To me, Lisp is all about ergonomics.<br/>
<br/>
I've tried to capture some of the pragmatism of Common Lisp and combine it with good ideas from Scheme, Clojure, Perl, Python and Ruby; while taking the opportunity to scratch a couple of personal itches along the way.

## bindings
Bindings come in two flavors, unscoped compile time and scoped runtime.

### compile time
New compile time bindings may be introduced using `define`.

```
  (^ foo []
    (define bar (do (say "compiling") 1)
            baz 2)
    (+ bar baz))

compiling

  (foo)

3

  bar

Error in repl@1:1:
Unknown identifier: bar
```

### runtime
New runtime bindings may be introduced using `let`.

```
  (let [x 1 y (+ x 2)]
    (+ x y))

3
```

## references
Most types are value types; that is, you can't modify their values outside of the scope they are bound in. References reintroduce action at a distance in a more explicit manner. New references may be formed by prefixing any expression with `&`.

```
  &42

&42
```

Dereferencing is as simple as calling without arguments.

```
  (&42)

42
```

When called with an argument, the referenced value is updated.

```
  (&_ 42)

&42
```
```
  (let [x &_]
    (x 42)
    x)

&42
```