#include <assert.h>
#include <stdio.h>

#define IS_A(elem, T) _Generic((elem), T: 1, default: 0)

#define match(Instance) \
  for(typeof(Instance)* _ref = &Instance; _ref != 0; _ref = 0)\
    switch (Instance.kind)

#define cat_impl(A, B) A##B
#define cat(A, B) cat_impl(A, B)

#define as(FieldType, FieldName)\
  break;\
  case GetEnumVal(*_ref, FieldType):\
    FieldType FieldName = _ref-> _##FieldType;

#define declval(T) (*(T*)0)

#define RESERVED 0xFFFFFFFF

// Need to find a better mechanism for this. This only fails if you have two missing as's
#define GetEnumVal(Suminst, FieldType) _Generic(Suminst,\
  Foo: _Generic(declval(FieldType),\
    int: Fooint,\
    char: Foochar,\
    default: RESERVED),\
  Bar: _Generic(declval(FieldType),\
    char: Barchar,\
    float: Barfloat,\
    default: RESERVED\
  )\
)

typedef struct
{
  enum {
    Fooint,
    Foochar
  } kind;
  union {
    int _int;
    char _char;
  };
} Foo;

Foo set_foo_int(const int i)
{
  Foo f;
  f.kind = Fooint;
  f._int = i;
  return f;
}

Foo set_foo_char(const char value)
{
  Foo f;
  f.kind = Foochar;
  f._char = value;
  return f;
}

typedef struct
{
  enum {
    Barchar,
    Barfloat
  } kind;
  union {
    char _char;
    float _float;
  };
} Bar;

Bar set_bar_char(const char value)
{
  Bar inst;
  inst.kind = Barchar;
  inst._char = value;
  return inst;
}

Bar set_bar_float(const float value)
{
  Bar inst;
  inst.kind = Barfloat;
  inst._float = value;
  return inst;
}


int main()
{
  Foo f = set_foo_int(30);

  match(f)
  {
    as(int, i) {
      printf("%d\n", i);
    }
    as(char, c)
    {
      printf("%c\n", c);
    }
  }
  return 0;
}
