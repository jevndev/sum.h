#include <assert.h>
#include <stdio.h>

#define COMMA                     ,
#define ARG_1( _1, ... )          _1
#define ARG_2( _1, _2, ... )      _2
#define ARG_3( _1, _2, _3, ... )  _3
#define IF_DEF_MAKE_SLOT( macro ) ARG_3( macro, ARG_1( macro, ): ((ARG_2( macro, ))0) COMMA, , )

#define GetType( T ) typeof(_Generic( (*((T* )0)), \
  IF_DEF_MAKE_SLOT( SLOT_1 )          \
  IF_DEF_MAKE_SLOT( SLOT_2 )          \
  IF_DEF_MAKE_SLOT( SLOT_3 )          \
  IF_DEF_MAKE_SLOT( SLOT_4 )          \
  IF_DEF_MAKE_SLOT( SLOT_5 )          \
  IF_DEF_MAKE_SLOT( SLOT_6 )          \
  IF_DEF_MAKE_SLOT( SLOT_7 )          \
  IF_DEF_MAKE_SLOT( SLOT_8 )          \
  default: ((void*)0)\
))

#define SLOT_1 int, char
#define SLOT_2 char, float

#define IS_A(elem, T) _Generic((elem), T: 1, default: 0)

#define match(Instance) \
  for(typeof(Instance)* _ref = &Instance; _ref != 0; _ref = 0)\
    switch (Instance.kind)

#define _current_match_type() Foo

#define cat_impl(A, B) A##B
#define cat(A, B) cat_impl(A, B)

#define as(FieldType, FieldName)\
  break;\
  case cat(_current_match_type(), FieldType):\
    FieldType FieldName = _ref-> _##FieldType;


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

int main()
{
  Foo f;

  f.kind = Foochar;
  f._int = 'a';

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
