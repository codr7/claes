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

claes v4
may the source be with you

  (say "hello" "world")

hello world
_
```

## language
To me, Lisp is all about ergonomics.<br/>
<br/>
I've tried to capture some of the pragmatism of Common Lisp and combine it with good ideas from Scheme, Clojure, Perl, Python and Ruby; while taking the opportunity to scratch a couple of personal itches along the way.

## nil
The `Nil` type has one value, `_`.

## bits
The `Bit` type has two values, `T` and `F`.

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
  (let [x 1 
        y (+ x 2)]
    y)

3
```

#### updates
Some macros update bindings behind the curtain, `decr` and `push` are two examples.<br/>
Runtime bindings may be updated using `set`.<br/>
<br/>
The following exmaple deserves a bit of an explanation. First we bind `foo` and `bar` to their initial values; then we decrease `foo` to `0`, `bar` is still `2` at this point. Then we re-bind `foo` to a vector containing both values, `bar` to an identical vector; and finally push 42 to `foo`.

```
  (let [foo 1 
        bar 2]
    (decr foo)
    (set foo [foo bar] 
         bar foo)
    (push foo 42)
    foo:bar)

[0 2 42]:[0 2]
```

## methods
New methods may be defined using `^`.

```
  (^ foo [x]
    x)

  (foo 42)
```

Leaving out the name creates a lambda.

```
  (let [f (^ [x] x)]
    (f 42))

42
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

## loops
`for` may be used to iterate through any sequence.

```
  (^ sum [n]
    (let [result 0]
      (for i n
        (set result (+ result i)))

      result))

6
```

Recursion is another option, tail call optimization is guaranteed to be performed where applicable.

```
  (^ sum [n]
    (^ helper [i result]
      (if (= i n)
        result
	(helper (+ i 1) (+ result i))))

    (helper 0 0))

  (sum 4)

6
```