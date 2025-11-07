#ifndef _SUM_H__FIRST_INCLUDE
#define _SUM_H__FIRST_INCLUDE

// TODO: use generic expand idiom thing to make recursive

// The below block contains the code that controls how many fields this library supports. Feel free
// to adapt it to your needs
// =================================================================================================
// clang-format off

#define _SUM_H__NARGS_IMPL(ElementTuple,                   A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A12, A13, A14, A15, A16,  N, ...)  N
#define _SUM_H__NARGS(...) _SUM_H__NARGS_IMPL(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 09, 08, 07,  06,  05,  04,  03,  02,  01, 00)

#define _SUM_H__FOREACH_EVAL(Macro, Closure, Element, I) Macro(Closure, Element, I)
#define _SUM_H__FOREACH_00(Macro, Closure, Element)      _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 00)
#define _SUM_H__FOREACH_01(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 01) _SUM_H__FOREACH_00(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_02(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 02) _SUM_H__FOREACH_01(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_03(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 03) _SUM_H__FOREACH_02(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_04(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 04) _SUM_H__FOREACH_03(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_05(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 05) _SUM_H__FOREACH_04(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_06(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 06) _SUM_H__FOREACH_05(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_07(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 07) _SUM_H__FOREACH_06(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_08(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 08) _SUM_H__FOREACH_07(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_09(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 09) _SUM_H__FOREACH_08(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_10(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 10) _SUM_H__FOREACH_09(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_11(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 11) _SUM_H__FOREACH_10(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_12(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 12) _SUM_H__FOREACH_11(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_13(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 13) _SUM_H__FOREACH_12(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_14(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 14) _SUM_H__FOREACH_13(Macro, Closure, __VA_ARGS__)
#define _SUM_H__FOREACH_15(Macro, Closure, Element, ...) _SUM_H__FOREACH_EVAL(Macro, Closure, Element, 15) _SUM_H__FOREACH_14(Macro, Closure, __VA_ARGS__)

// clang-format on
// =================================================================================================

#define _SUM_H__FOREACH_DISPATCH(Macro, Closure, Count, ...)                                 \
  _SUM_H__FOREACH_##Count(Macro, Closure, __VA_ARGS__)

#define _SUM_H__FOREACH_EXPAND_COUNT(Macro, Closure, Count, ...)                             \
  _SUM_H__FOREACH_DISPATCH(Macro, Closure, Count, __VA_ARGS__)

// Macro takes (Closure, Element, i)
#define _SUM_H__FOREACH(Macro, Closure, ...)                                                 \
  _SUM_H__FOREACH_EXPAND_COUNT(Macro, Closure, _SUM_H__NARGS(__VA_ARGS__), __VA_ARGS__)

// Macro takes (SumType, FieldType, I)
#define _SUM_H__FOREACH_FIELD(Macro, SumType, ...)                                                 \
  _SUM_H__FOREACH(Macro, SumType, __VA_ARGS__)

#define _SUM_H__CAT_IMPL(A, B) A##B
#define _SUM_H__CAT(A, B) _SUM_H__CAT_IMPL(A, B)
#define _SUM_H__CAT_3(A, B, C) A##B##C

#define _SUM_H__UNWRAP_IMPL(...) __VA_ARGS__
#define _SUM_H__UNWRAP(A) _SUM_H__UNWRAP_IMPL A
#define _SUM_H__UNWRAP_DEFINITION_IMPL(Name, Fields) Name, _SUM_H__UNWRAP(Fields)
#define _SUM_H__UNWRAP_DEFINITION(Definition) _SUM_H__UNWRAP_DEFINITION_IMPL(Definition)

#define _SUM_H__GET_SUMTYPE_NAME(Name, ...) Name
#define _SUM_H__GET_ENUM_FIELD_NAME(SumType, FieldType) SumType##FieldType
#define _SUM_H__GET_UNION_FIELD_NAME(FieldType) _##FieldType

#define _SUM_H__GENERATE_ENUM_FIELD(SumType, FieldType, I)                                            \
  , _SUM_H__GET_ENUM_FIELD_NAME(SumType, FieldType)
#define _SUM_H__GENERATE_ENUM(...)                                                                 \
  enum {                                                                                           \
    _SUM_H__CAT(_SUM_H__GET_SUMTYPE_NAME(__VA_ARGS__), 0) = 0                                      \
    _SUM_H__FOREACH_FIELD(_SUM_H__GENERATE_ENUM_FIELD, __VA_ARGS__)                                \
  }

#define _SUM_H__GENERATE_UNION_FIELD(SumType, FieldType, I)                                           \
  FieldType _SUM_H__GET_UNION_FIELD_NAME(FieldType);
#define _SUM_H__GENERATE_UNION(...)                                                                \
  union {                                                                                          \
    _SUM_H__FOREACH_FIELD(_SUM_H__GENERATE_UNION_FIELD, __VA_ARGS__)                               \
  }

#define _SUM_H__GENERATE_SETTER(SumType, FieldType, I)                                                \
  SumType _SUM_H__CAT_3(SumType, _set_, FieldType)(FieldType new_value) {                          \
    SumType inst;                                                                                  \
    inst._kind = _SUM_H__GET_ENUM_FIELD_NAME(SumType, FieldType);                                  \
    inst._data._SUM_H__GET_UNION_FIELD_NAME(FieldType) = new_value;                                \
    return inst;                                                                                   \
  }

#define _SUM_H__GENERATE_SETTERS(...) _SUM_H__FOREACH_FIELD(_SUM_H__GENERATE_SETTER, __VA_ARGS__)

#define _SUM_H__GENERATE_SUM(...)                                                                  \
  typedef struct {                                                                                 \
    _SUM_H__GENERATE_ENUM(__VA_ARGS__) _kind;                                                      \
    _SUM_H__GENERATE_UNION(__VA_ARGS__) _data;                                                     \
  } _SUM_H__GET_SUMTYPE_NAME(__VA_ARGS__);                                                         \
  _SUM_H__GENERATE_SETTERS(__VA_ARGS__)

#define match(Instance)                                                                            \
  for(typeof(Instance)* _ref = &Instance; _ref != 0; _ref = 0)                                     \
    switch (Instance.kind)

#define as(FieldType, FieldName)                                                                   \
  break;                                                                                           \
  case _SUM_H__GET_ENUM_VALUE(*_ref, FieldType):                                                   \
    FieldType FieldName = _ref->_data. _SUM_H__GET_UNION_FIELD_NAME(FieldType);

#define COMMA()               ,
#define ARG_2_( _1, _2, ... ) _2
#define ARG_2( ... )          ARG_2_( __VA_ARGS__ )
#define INCL( ... )           __VA_ARGS__
#define OMIT( ... )
#define IF_DEF( macro )       ARG_2( COMMA macro () INCL, OMIT, )

#define _SUM_H__GET_ENUM_VALUE( SumTypeInstance, FieldType ) _Generic( (val),        \
  IF_DEF( _SUM_H__SLOT_1 )( _SUM_H__GENERATE_MATCH_SUMTYPE_BODY_N(01), ) \
  IF_DEF( _SUM_H__SLOT_2 )( _SUM_H__GENERATE_MATCH_SUMTYPE_BODY_N(02), ) \
  IF_DEF( _SUM_H__SLOT_3 )( _SUM_H__GENERATE_MATCH_SUMTYPE_BODY_N(03), ) \
  IF_DEF( _SUM_H__SLOT_4 )( _SUM_H__GENERATE_MATCH_SUMTYPE_BODY_N(04), ) \
)

#define _SUM_H__GENERATE_MATCH_SUMTYPE_BODY_N(N)

#define _SUM_H__SUMTYPE_FIELD(N, M) _SUM_H_SUMTYPE_##N##_FIELD_##M

#define _SUM_H__MAKE_TYPEDEF_IMPL(N, SumType, FieldType, I) typedef FieldType _SUM_H__SUMTYPE_FIELD(N, I);
#define _SUM_H__MAKE_TYPEDEF_EXPAND(Expanded, FieldType, I) _SUM_H__MAKE_TYPEDEF_IMPL(Expanded, FieldType, I)
#define _SUM_H__MAKE_TYPEDEF(Closure, Field, I) _SUM_H__MAKE_TYPEDEF_EXPAND(_SUM_H__UNWRAP(Closure), Field, I)

#define _SUM_H__DEF_SLOT_N_IMPL(N, SumType, ...) _SUM_H__FOREACH(_SUM_H__MAKE_TYPEDEF, (N, SumType), __VA_ARGS__)
#define _SUM_H__DEF_SLOT_N_EXPAND(N, Expanded) _SUM_H__DEF_SLOT_N_IMPL(N, Expanded)
#define _SUM_H__DEF_SLOT_N(N, NewSum) _SUM_H__DEF_SLOT_N_EXPAND(N, _SUM_H__UNWRAP_DEFINITION_IMPL(NewSum))

#else

#ifndef NEW_SUM
#error NEW_SUM is undefined, put the definition of the new sum type in it
#endif

_SUM_H__GENERATE_SUM(_SUM_H__UNWRAP_DEFINITION(NEW_SUM))
#if     !defined( _SUM_H__SLOT_1 )
#define _SUM_H__SLOT_1
_SUM_H__DEF_SLOT_N(01, NEW_SUM)
#elif   !defined( _SUM_H__SLOT_2 )
#define _SUM_H__SLOT_2
_SUM_H__DEF_SLOT_N(02, NEW_SUM)
#elif   !defined( _SUM_H__SLOT_3 )
#define _SUM_H__SLOT_3
_SUM_H__DEF_SLOT_N(03, NEW_SUM)
#elif   !defined( _SUM_H__SLOT_4 )
#define _SUM_H__SLOT_4
_SUM_H__DEF_SLOT_N(04, NEW_SUM)
#else
#error Too many SumTypes
#endif

#undef NEW_SUM
#endif
