#ifndef SUM_H
#define SUM_H

// Utilities

#define _SUM_H__UNWRAP_IMPL(...) __VA_ARGS__
#define _SUM_H__UNWRAP(A) _SUM_H__UNWRAP_IMPL A

#define _SUM_H__GET_TYPE_IMPL_2(Type, Name) Type
#define _SUM_H__GET_TYPE_IMPL(...) _SUM_H__GET_TYPE_IMPL_2(__VA_ARGS__)
#define _SUM_H__GET_TYPE(Tuple) _SUM_H__GET_TYPE_IMPL(_SUM_H__UNWRAP(Tuple))

#define _SUM_H__GET_NAME_IMPL_2(Type, Name) Name
#define _SUM_H__GET_NAME_IMPL(...) _SUM_H__GET_NAME_IMPL_2(__VA_ARGS__)
#define _SUM_H__GET_NAME(Tuple) _SUM_H__GET_NAME_IMPL(_SUM_H__UNWRAP(Tuple))

// clang-format off

// TODO: use generic expand idiom thing to make recursive

#define _SUM_H__NARGS_IMPL(ElementTuple,                   A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A12, A13, A14, A15, A16, N, ...)  N
#define _SUM_H__NARGS(...) _SUM_H__NARGS_IMPL(__VA_ARGS__, 15, 14, 13, 12, 11, 10, 9,   8,  7,   6,   5,   4,   3,   2,   1, 0)

#define _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) Macro(TypeName, ElementTuple)

#define _SUM_H__FOR_ELEMENT_TUPLES_0(TypeName, Macro,  ElementTuple)      _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro)
#define _SUM_H__FOR_ELEMENT_TUPLES_1(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_0(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_2(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_1(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_3(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_2(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_4(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_3(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_5(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_4(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_6(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_5(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_7(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_6(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_8(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_7(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_9(TypeName, Macro,  ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_8(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_10(TypeName, Macro, ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_9(TypeName, Macro,  __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_11(TypeName, Macro, ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_10(TypeName, Macro, __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_12(TypeName, Macro, ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_11(TypeName, Macro, __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_13(TypeName, Macro, ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_12(TypeName, Macro, __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_14(TypeName, Macro, ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_13(TypeName, Macro, __VA_ARGS__)
#define _SUM_H__FOR_ELEMENT_TUPLES_15(TypeName, Macro, ElementTuple, ...) _SUM_H__FOR_ELEMENT_TUPLES_EVAL(TypeName, ElementTuple, Macro) _SUM_H__FOR_ELEMENT_TUPLES_14(TypeName, Macro, __VA_ARGS__)

// clang-format on

#define _SUM_H__FOR_ELEMENT_TUPLES_DISPATCH(TypeName, Macro, Count, ...)                           \
  _SUM_H__FOR_ELEMENT_TUPLES_##Count(TypeName, Macro, __VA_ARGS__)

#define _SUM_H__FOR_ELEMENT_TUPLES_EXPAND_COUNT(TypeName, Macro, Count, ...)                       \
  _SUM_H__FOR_ELEMENT_TUPLES_DISPATCH(TypeName, Macro, Count, __VA_ARGS__)

// Macro takes (TypeName, ElementTuple)
#define _SUM_H__FOR_ELEMENT_TUPLES_VAR(TypeName, Macro, ...)                                       \
  _SUM_H__FOR_ELEMENT_TUPLES_EXPAND_COUNT(TypeName, Macro, _SUM_H__NARGS(__VA_ARGS__), __VA_ARGS__)

#define _SUM_H__FOR_ELEMENT_TUPLES(TypeName, Macro, ElementTuples)                                 \
  _SUM_H__FOR_ELEMENT_TUPLES_VAR(TypeName, Macro, _SUM_H__UNWRAP(ElementTuples))

#define _SUM_H__EXPAND_ENUM_ARGS_0(TypeName, ElementTuple)       _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple)
#define _SUM_H__EXPAND_ENUM_ARGS_1(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_0(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_2(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_1(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_3(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_2(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_4(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_3(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_5(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_4(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_6(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_5(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_7(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_6(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_8(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_7(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_9(TypeName, ElementTuple, ...)  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_8(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_10(TypeName, ElementTuple, ...) _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_9(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_11(TypeName, ElementTuple, ...) _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_10(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_12(TypeName, ElementTuple, ...) _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_11(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_13(TypeName, ElementTuple, ...) _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_12(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_14(TypeName, ElementTuple, ...) _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_13(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_15(TypeName, ElementTuple, ...) _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_14(TypeName, __VA_ARGS__)


#define _SUM_H__EXPAND_UNION_ARGS_0(ElementTuple)        _SUM_H__EXPAND_UNION_ARG(ElementTuple);
#define _SUM_H__EXPAND_UNION_ARGS_1(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_0(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_2(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_1(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_3(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_2(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_4(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_3(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_5(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_4(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_6(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_5(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_7(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_6(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_8(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_7(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_9(ElementTuple, ...)   _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_8(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_10(ElementTuple, ...)  _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_9(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_11(ElementTuple, ...)  _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_10(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_12(ElementTuple, ...)  _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_11(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_13(ElementTuple, ...)  _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_12(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_14(ElementTuple, ...)  _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_13(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_15(ElementTuple, ...)  _SUM_H__EXPAND_UNION_ARG(ElementTuple); _SUM_H__EXPAND_UNION_ARGS_14(__VA_ARGS__)

#define _SUM_H__EXPAND_ENUM_ARG_IMPL_2(TypeName, ElementName) TypeName##_##ElementName
#define _SUM_H__EXPAND_ENUM_ARG_IMPL(TypeName, ElementName)                                        \
  _SUM_H__EXPAND_ENUM_ARG_IMPL_2(TypeName, ElementName)
#define _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple)                                            \
  _SUM_H__EXPAND_ENUM_ARG_IMPL(TypeName, _SUM_H__GET_NAME(ElementTuple))

#define _SUM_H__GENERATE_ENUM_FIELDS_DISPATCH(TypeName, Count, ...)                                \
  _SUM_H__EXPAND_ENUM_ARGS_##Count(TypeName, __VA_ARGS__)
#define _SUM_H__GENERATE_ENUM_FIELDS_EXPAND_NARGS(TypeName, Count, ...)                            \
  _SUM_H__GENERATE_ENUM_FIELDS_DISPATCH(TypeName, Count, __VA_ARGS__)
#define _SUM_H__GENERATE_ENUM_FIELDS_IMPL(TypeName, ...)                                           \
  _SUM_H__GENERATE_ENUM_FIELDS_EXPAND_NARGS(TypeName, _SUM_H__NARGS(__VA_ARGS__), __VA_ARGS__)

#define _SUM_H__GENERATE_ENUM_FIELDS(TypeName, ElementTuples)                                      \
  _SUM_H__GENERATE_ENUM_FIELDS_IMPL(TypeName, _SUM_H__UNWRAP(ElementTuples))

#ifdef SUM_H_DONT_GENERATE_INVALID_KIND_ENTRY
#define _SUM_H_GENERATE_INVALID_KIND_ENTRY(TypeName)
#else
#define _SUM_H_GENERATE_INVALID_KIND_ENTRY(TypeName) TypeName##_INVALID = 0,
#endif

#define _SUM_H__ENUM_NAME(TypeName) TypeName##_Kind
#define _SUM_H__MAKE_ENUM(TypeName, ElementTuples)                                                 \
  typedef enum _SUM_H__ENUM_NAME(TypeName) {                                                       \
    _SUM_H_GENERATE_INVALID_KIND_ENTRY(TypeName)                                                   \
        _SUM_H__GENERATE_ENUM_FIELDS(TypeName, ElementTuples)                                      \
  } _SUM_H__ENUM_NAME(TypeName);

// Union Generation Code

#define _SUM_H__EXPAND_UNION_ARG_IMPL_2(ElementType, ElementName) ElementType ElementName
#define _SUM_H__EXPAND_UNION_ARG_IMPL(ElementType, ElementName)                                    \
  _SUM_H__EXPAND_UNION_ARG_IMPL_2(ElementType, ElementName)
#define _SUM_H__EXPAND_UNION_ARG_UNWRAP(Elements) _SUM_H__EXPAND_UNION_ARG_IMPL(Elements)
#define _SUM_H__EXPAND_UNION_ARG(ElementTuple)                                                     \
  _SUM_H__EXPAND_UNION_ARG_UNWRAP(_SUM_H__UNWRAP(ElementTuple))

#define _SUM_H__GENERATE_UNION_FIELDS_DISPATCH(Count, ...)                                         \
  _SUM_H__EXPAND_UNION_ARGS_##Count(__VA_ARGS__)
#define _SUM_H__GENERATE_UNION_FIELDS_EXPAND_NARGS(Count, ...)                                     \
  _SUM_H__GENERATE_UNION_FIELDS_DISPATCH(Count, __VA_ARGS__)
#define _SUM_H__GENERATE_UNION_FIELDS_IMPL(...)                                                    \
  _SUM_H__GENERATE_UNION_FIELDS_EXPAND_NARGS(_SUM_H__NARGS(__VA_ARGS__), __VA_ARGS__)

#define _SUM_H__GENERATE_UNION_FIELDS(ElementTuples)                                               \
  _SUM_H__GENERATE_UNION_FIELDS_IMPL(_SUM_H__UNWRAP(ElementTuples))

#define _SUM_H__UNION_NAME(TypeName) TypeName##_Data
#define _SUM_H__MAKE_UNION(TypeName, ElementTuples)                                                \
  typedef union _SUM_H__UNION_NAME(TypeName) {                                                     \
    _SUM_H__GENERATE_UNION_FIELDS(ElementTuples)                                                   \
  } _SUM_H__UNION_NAME(TypeName);

// Struct Generation

#define _SUM_H__MAKE_STRUCT(TypeName, ElementTuples)                                               \
  typedef struct TypeName {                                                                        \
    enum _SUM_H__ENUM_NAME(TypeName) kind;                                                         \
    union _SUM_H__UNION_NAME(TypeName) data;                                                       \
  } TypeName

#define SUM_H_SUM(TypeName, ElementTuples)                                                         \
  _SUM_H__MAKE_ENUM(TypeName, ElementTuples)                                                       \
  _SUM_H__MAKE_UNION(TypeName, ElementTuples)                                                      \
  _SUM_H__MAKE_STRUCT(TypeName, ElementTuples)

#ifdef SUM_H_STRIP_PREFIX
#define SUM SUM_H_SUM
#endif

#endif
