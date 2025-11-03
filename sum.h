#ifndef _SUM_H__FIRST_INCLUDE
#define _SUM_H__FIRST_INCLUDE

// TODO: use generic expand idiom thing to make recursive

// The below block contains the code that controls how many fields this library supports. Feel free
// to adapt it to your needs
// =================================================================================================
// clang-format off

#define _SUM_H__NARGS_IMPL(ElementTuple,                   A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A12, A13, A14, A15, A16,  N, ...)  N
#define _SUM_H__NARGS(...) _SUM_H__NARGS_IMPL(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 09, 08, 07,  06,  05,  04,  03,  02,  01, 00)

#define _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) Macro(SumType, FieldType)

#define _SUM_H__FOREACH_FIELD_00(Macro, SumType, FieldType)      _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType)
#define _SUM_H__FOREACH_FIELD_01(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_00(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_02(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_01(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_03(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_02(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_04(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_03(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_05(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_04(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_06(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_05(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_07(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_06(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_08(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_07(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_09(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_08(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_10(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_09(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_11(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_10(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_12(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_11(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_13(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_12(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_14(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_13(Macro, SumType, __VA_ARGS__)
#define _SUM_H__FOREACH_FIELD_15(Macro, SumType, FieldType, ...) _SUM_H__FOREACH_FIELD_EVAL(Macro, SumType, FieldType) _SUM_H__FOREACH_FIELD_14(Macro, SumType, __VA_ARGS__)

// clang-format on
// =================================================================================================

#define _SUM_H__FOREACH_FIELD_DISPATCH(Macro, SumType, Count, ...)                            \
  _SUM_H__FOREACH_FIELD_##Count(Macro, SumType, __VA_ARGS__)

#define _SUM_H__FOREACH_FIELD_EXPAND_COUNT(Macro, SumType, Count, ...)                        \
  _SUM_H__FOREACH_FIELD_DISPATCH(Macro, SumType, Count, __VA_ARGS__)

// Macro takes (SumType, FieldType)
#define _SUM_H__FOREACH_FIELD(Macro, SumType, ...)                                                 \
  _SUM_H__FOREACH_FIELD_EXPAND_COUNT(Macro, SumType, _SUM_H__NARGS(__VA_ARGS__), __VA_ARGS__)

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

#define _SUM_H__GENERATE_ENUM_FIELD(SumType, FieldType)                                            \
  , _SUM_H__GET_ENUM_FIELD_NAME(SumType, FieldType)
#define _SUM_H__GENERATE_ENUM(...)                                                                 \
  enum {                                                                                           \
    _SUM_H__CAT(_SUM_H__GET_SUMTYPE_NAME(__VA_ARGS__), 0) = 0                                      \
    _SUM_H__FOREACH_FIELD(_SUM_H__GENERATE_ENUM_FIELD, __VA_ARGS__)                                \
  }

#define _SUM_H__GENERATE_UNION_FIELD(SumType, FieldType)                                           \
  FieldType _SUM_H__GET_UNION_FIELD_NAME(FieldType);
#define _SUM_H__GENERATE_UNION(...)                                                                \
  union {                                                                                          \
    _SUM_H__FOREACH_FIELD(_SUM_H__GENERATE_UNION_FIELD, __VA_ARGS__)                               \
  }

#define _SUM_H__GENERATE_SETTER(SumType, FieldType)                                                \
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

#else

#ifndef NEW_SUM
#error NEW_SUM is undefined, put the definition of the new sum type in it
#endif

_SUM_H__GENERATE_SUM(NEW_SUM)

#undef NEW_SUM
#endif
