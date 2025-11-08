#define SUM_H_STRIP_PREFIX
#include "sum.h"
#include <stdio.h>

#define NEW_SUM Foo, (int, char)
#include "sum.h"

#define NEW_SUM Bar, (float, int)
#include "sum.h"


int main()
{
  Foo foo = Foo_set_int(1);

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

  Bar bar = Bar_set_float(1.0f);

  match(bar)
  {
    as(float, f)
    {
      printf("Bar float! %f\n", f);
    }
    as (int, i)
    {
      printf("Bar int! %d\n", i);
    }
  }

  return 0;
}
