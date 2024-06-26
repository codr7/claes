# ![Logo](logo.png) intro
This project aims to implement a custom Lisp in C++.<br/>
<br/>
Most of the code in this document is included in the [test suite](https://github.com/codr7/claes/blob/main/tests.claes).<br/>
<br/>
The codebase has very few dependencies, doesn't use exceptions, and currently weighs in at around 6 kloc.

## setup
The codebase requires CMake and a C++20-compiler to build.

Launching the binary without arguments starts a REPL, `rlwrap` may be used to add support for line editing.

```
git clone https://github.com/codr7/claes.git
cd claes
mkdir build
cd build
cmake -DUSE_CURL=OFF -DUSE_SQLITE=OFF ..
make claes
rlwrap ./claes

claes v8
may the src/ be with you

  (say "hello" "world")

hello world
_
```

## language
To me, Lisp is all about ergonomics.<br/>
<br/>
I've tried to capture some of the pragmatism of Common Lisp and combine it with good ideas from Scheme, Clojure, Perl, Python and Ruby; while taking the opportunity to scratch a couple of personal itches along the way.<br/>
<br/>
It's still very much a work in progress, but already perfectly usable as an embedded scripting/configuration/template language; which is its primary intended use case.

## nil
The `Nil` type has one value, `_`.

## bits
The `Bit` type has two values, `T` and `F`.

`or` short-circuits to return the first true value.
```
  (or 0 F)

F
  (or 42 0)

42
```

`and` short-circuits to return the first false value.
```
  (and 0 42)

0

  (and "abc" 42)

42
```

## pairs
Pairs may be formed by putting `:` between two values.

```
  'foo:42

'foo:42
```

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
<br/>
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

### lambdas
Leaving out the name creates a lambda.

```
  (let [f (^ [x] x)]
    (f 42))

42
```

### vectors
A vector is defined as a value-based single dimensional dynamic array.<br/>
Vectors are used to represent most collections/sequences in the syntax.<br/>

New vectors may be created by calling the type.
```
  (Vector 1 2 3)

[1 2 3]
```

Or using the literal form.
```
  [1 2 3]

[1 2 3]
```

Calling a vector queries or updates depending on the number of arguments.

```
  ('[foo bar baz] 1)

'bar
```
```
  (let [v '[foo bar baz]]
    (v 1 'qux)
    v)

['foo 'qux 'baz]
```

### maps
A map is defined as a value based, ordered mapping.<br/>
Maps and pairs are very tightly related.<br/>

New maps may be created by calling the type.
```
  (Map 'foo:1 'bar:2 'baz:3)

{'bar:2 'baz:3 'foo:1}
```

Or using the literal form.
```
  '{foo:1 bar:2 baz:3}

{'bar:2 'baz:3 'foo:1}
```

Calling a map queries or updates depending on the number of arguments.

```
  ('{foo:1 bar:2 baz:3} 'bar)

2
```
```
  (let [m '{foo:1 bar:2 baz:3}]
    (m 'bar 4)
    m)

{'bar:4 'baz:3 'foo:1}
```

### varargs
Methods may be defined to accept a variable number of arguments by suffixing the last argument with `*`.

```
  (^ foo [x*]
    x)
    
  (foo 1 2 3)

[1 2 3]
```

### splats
`*` may also be used to splat arguments into calls.

```
  (+ [1 2 3]*)

6
```

Which could be expressed even more succinctly.
```
  (+ 4*)

6
```

### fexprs
Quoting argument names creates fexprs, arguments may be evaluated by calling them.

```
  (^ foo ['x]
    x)
  
  (foo (say "evaluating"))

(Expr (say "evaluating"))

  ((foo (say "evaluating")))

evaluating
```

## quoting
Prefixing any expression with `'` wraps it up as a value and pushes it on the stack instead of evaluating it.

```
  'foo

'foo

  'foo:'bar

'foo:'bar

  '[foo bar baz]

['foo 'bar 'baz]

  '(foo 1 2 3)

'foo:[1 2 3]
```

### unquoting
Within any quoted context, `,` may be used to temporarily escape it.

```
  (let [x 42]
    '[foo ,x bar])

['foo 42 'bar]
```

### symbols
Symbols are quoted identifiers, the same symbol always refers to the same adress in memory; which makes them cheaper to compare for equality than strings.

```
  (= 'foo 'foo)
```

Any values may be turned into a symbol using `Sym`.

```
  (Sym "foo" 'bar 42 T)

'foobar42T
```

`String` may be used to get a symbols name.

```
  (String 'foo)

"foo"
```

## references
Most types are value types; that is, you can't modify their values outside of the scope they are bound in. References reintroduce action at a distance in a more explicit manner. New references may be formed by prefixing any expression with `&`.

```
  &42

&42
```

Dereferencing is as easy as calling without arguments.

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

## json
The [JSON](https://www.json.org/json-en.html) format is tightly integrated into the language.

Applicable values may be converted to json using `js`.
```
  (js [42 .123 "foo" 'bar _ T 1:2])

"[42, 0.123, \"foo\", \"bar\", null, true, [1, 2]]"
```

Values may be parsed from json strings using `parse-js`.

```
  (parse-js "[42, 0.123, \"foo\", \"bar\", null, true, [1, 2]]")

[42 .123 "foo" 'bar _ T 1:2]
```

## debugging
`debug` may be used to enable/disable debugging.

```
  (debug)

T
```

`dump` may be used to dump any values to standard output.

```
  (dump "foo" 42 +)

"foo" 42 (Method +)
```

`trace` may be used to enable/disable tracing of evaluated VM operations.

```
  (trace)
  (+ 1 2)

1 Push value: T
3 Push value: 1
5 Push value: 2
7 CallDirect target: (Method +) arity: 2 loc: repl@2:3
9 Exit
3
```

`loc` may be used to get the current source location. Note that debugging must be enabled when the code is emitted for `loc` to work properly.

```
  (debug)
  (say "line 2")
  (loc)

  line 2
  repl@3:1
```

`stop` may be used to (temporarily) stop evaluation; it prints the current source location, call chain and stack when called, and finally the next pc and operation. The `d>` prompt indicates that we are in the debugger, `q` exits back to the REPL.

```
 (^ foo []
   (stop)
   42)

_
  (foo)

Stopped in repl@2:3
(Method foo) in repl@1:1

[]

3 Push value: 42
d> q
_
```

`s` may be used to keep evaluating until the next macro/method call. Note that debugging must be enabled when the code is emitted for stepping to work properly.

```
  (debug)

  (^ foo []
    (stop)
    42
    (stop))

  (foo)

Stopped in repl@2:5
(Method foo) in repl@1:3

[]

7 Push value: 42
d> s
Stopped in repl@4:5
(Method foo) in repl@1:3

[42]

10 Return
d> s
42
```

`ss` may be used to single step VM operations.

```
 (debug)

 (^ foo []
   (stop)
   42)

 (foo)

Stopped in repl@3:7
(Method foo) in repl@5:5

[T]

6 Push value: 42
d> ss
Stopped in repl@3:7
(Method foo) in repl@5:5

[T 42]

7 Return
d> ss
Stopped in repl@3:7

[T 42]

10 Exit
d> ss
42
```
