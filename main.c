#include <stdio.h>

#include "sum.h"

#define NEW_SUM Foo, int, char
#include "sum.h"

int main()
{
  Foo f = Foo_set_int(1);

  if (f._kind == Foochar)
  {
    printf("%c\n", f._data._char);
  } else if (f._kind == Fooint)
  {
    printf("%d\n", f._data._int);
  }

  return 0;
}

