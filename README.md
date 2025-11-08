# sum.h

sum.h is a header-only library for generating and using tagged unions in c

## How to use

```c
// Initialize the library
#define SUM_H_STRIP_PREFIX
#include "sum.h"

// Declare a new sum type (note the second include of sum.h after the declaration)
#define NEW_SUM Foo, (int, char)
#include "sum.h"

int main()
{
  Foo f = Foo_set_int(42);

  match(foo)
  {
    as(int, i)
    {
      printf("Foo int! %d\n", i);
    }
    as(char, c)
    {
      printf("Foo char! %c\n", c);
    }
  }
}
```

> [!WARNING]
> This library is in its infancy. There may be breaking API changes as more features get added.

### Restrictions

Due to the way that the library generates your data types, type names passed to it must be valid as part of an identifier. I.e. no qualifiers (`const`, `volatile`, etc.) and no pointers `*`. Just one contiguous set of letters, numbers and underscores. This can be circumvented by `typedef`-ing your types before declaring the sum type.

Giving more complex types a good name is a good practice though, so until I settle on a solution for this I'm going to say this is a feature and not a bug :)


### Stripping prefixes

This library is loosely [stb](https://github.com/nothings/stb/blob/master/)-like, especially in how it treats prefixes to avoid name collisions. However, if you find `SUM_H_*(...)` to be too verbose, defining `SUM_H_STRIP_PREFIX` before including `sum.h` the first timemakes the declaration into just `*(...)`.

## "Why did you do this that way?"

### "Why Sum?"

I like the interpretation of [algebraic data types](https://en.wikipedia.org/wiki/Algebraic_data_type) when it comes to type theory and I needed a good name. I could have gone with `variant`, as C++ did, or any of the [many other](https://en.wikipedia.org/wiki/Tagged_union) synoyms, but `sum type` was cute.

### "Why is the enum 'Kind' and not 'Type'?"

'Type' is an overloaded term. Especially when in C++ where you actually _might_ be passing around types. I find that saying "what kind of X is this?" instead of "what type of X is this?" disambiguates things.

### "This only supports N fields. What if I have M > N?"

Near the top of [sum.h](sum.h), there is a block which contains the implementation details for generating the code it does. It can be expanded to your needs

## Missing Features
- [ ] Using a smarter mechanism for counting generated sum type slots and fields to support arbitrarily high numbers without hard-coding
- [ ] Better protection around misuses of the api

## Licensing

This library is free for use under the [MIT license](LICENSE)
