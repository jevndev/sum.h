# sum.h

sum.h is a header-only library for generating and using tagged unions in c

## How to use

The following code:

```c
SUM(Foo, ((int, i), (char, c)));
```

results in this code being generated:

```c
typedef enum Foo_Kind {
  Foo_INVALID = 0,
  Foo_i,
  Foo_c
};

typedef union Foo_Data {
  int i;
  char c;
};

typedef struct Foo {
  enum Foo_Kind kind;
  union Foo_Data data;
};

```

Refer to [main.c](main.c) for an example (albeit contrived) use-case of this library.

> [!WARNING]
> This library is in its infancy. There may be breaking API changes as more features get added.

### Stripping prefixes

This library is loosely [stb](https://github.com/nothings/stb/blob/master/)-like, especially in how it treats prefixes to avoid name collisions. However, if you find `SUM_H_SUM(...)` to be too verbose, defining `SUM_H_STRIP_PREFIX` before including `sum.h` makes the declaration into just `SUM(...)`.

## Other customization points:

### `SUM_H_DONT_GENERATE_INVALID_KIND_ENTRY`

By default, sum.h will generate `<Type>_INVALID = 0` as the first entry in the enum. This is useful
to detect data that hasn't been properly intialized. define `SUM_H_DONT_GENERATE_INVALID_KIND_ENTRY` to disable this functionality

## "Why did you do this that way?"

### "Why Sum?"

I like the interpretation of [algebraic data types](https://en.wikipedia.org/wiki/Algebraic_data_type) when it comes to type theory and I needed a good name. I could have gone with `variant`, as C++ did, or any of the [many other](https://en.wikipedia.org/wiki/Tagged_union) synoyms, but `sum type` was cute.

### "Why is the enum 'Kind' and not 'Type'?"

'Type' is an overloaded term. Especially when in C++ where you actually _might_ be passing around types. I find that saying "what kind of X is this?" instead of "what type of X is this?" disambiguates things.

### "This only supports N fields. What if I have M > N?"

Near the top of [sum.h](sum.h), there is a block which contains the implementation details for generating the code it does. It can be expanded to your needs

## Missing Features

- [ ] Generating "match", "contains", "get", "set" functions
- [ ] Maybe support structs defined within a `SUM` invocation? Would be useful for ergonomics when making return types but very difficult and magic-y. Not sure yet.
- [ ] Add SUM_R (name pending) for defining sum types as returns of functions
- [ ] Generating COUNT entries for enums?

## Licensing

This library is free for use under the [MIT license](LICENSE)
