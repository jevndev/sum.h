#ifndef SUM_H
#define SUM_H

// Utilities
#define _NARGS_IMPL(ElementTuple, A1, A2, A3, N, ...) N
#define _NARGS(...) _NARGS_IMPL(__VA_ARGS__, 3, 2, 1, 0)

#define _UNWRAP_IMPL(...) __VA_ARGS__
#define _UNWRAP(A) _UNWRAP_IMPL A

#define _GET_TYPE_IMPL_2(Type, Name) Type
#define _GET_TYPE_IMPL(...) _GET_TYPE_IMPL_2(__VA_ARGS__)
#define _GET_TYPE(Tuple) _GET_TYPE_IMPL(_UNWRAP(Tuple))

#define _GET_NAME_IMPL_2(Type, Name) Name
#define _GET_NAME_IMPL(...) _GET_NAME_IMPL_2(__VA_ARGS__)
#define _GET_NAME(Tuple) _GET_NAME_IMPL(_UNWRAP(Tuple))

// Enum Generation Code

#define _EXPAND_ENUM_ARG_IMPL_2(TypeName, ElementName) TypeName##_##ElementName
#define _EXPAND_ENUM_ARG_IMPL(TypeName, ElementName) _EXPAND_ENUM_ARG_IMPL_2(TypeName, ElementName)
#define _EXPAND_ENUM_ARG(TypeName, ElementTuple)                                                   \
  _EXPAND_ENUM_ARG_IMPL(TypeName, _GET_NAME(ElementTuple))

// TODO: use generic expand idiom thing to make recursive
#define _EXPAND_ENUM_ARGS_0(TypeName, ElementTuple) _EXPAND_ENUM_ARG(TypeName, ElementTuple)
#define _EXPAND_ENUM_ARGS_1(TypeName, ElementTuple, ...)                                           \
  _EXPAND_ENUM_ARG(TypeName, ElementTuple), _EXPAND_ENUM_ARGS_0(TypeName, __VA_ARGS__)
#define _EXPAND_ENUM_ARGS_2(TypeName, ElementTuple, ...)                                           \
  _EXPAND_ENUM_ARG(TypeName, ElementTuple), _EXPAND_ENUM_ARGS_1(TypeName, __VA_ARGS__),
#define _EXPAND_ENUM_ARGS_3(TypeName, ElementTuple, ...)                                           \
  _EXPAND_ENUM_ARG(TypeName, ElementTuple), _EXPAND_ENUM_ARGS_2(TypeName, __VA_ARGS__),

#define _GENERATE_ENUM_FIELDS_DISPATCH(TypeName, Count, ...)                                       \
  _EXPAND_ENUM_ARGS_##Count(TypeName, __VA_ARGS__)
#define _GENERATE_ENUM_FIELDS_EXPAND_NARGS(TypeName, Count, ...)                                   \
  _GENERATE_ENUM_FIELDS_DISPATCH(TypeName, Count, __VA_ARGS__)
#define _GENERATE_ENUM_FIELDS_IMPL(TypeName, ...)                                                  \
  _GENERATE_ENUM_FIELDS_EXPAND_NARGS(TypeName, _NARGS(__VA_ARGS__), __VA_ARGS__)

#define _GENERATE_ENUM_FIELDS(TypeName, ElementTuples)                                             \
  _GENERATE_ENUM_FIELDS_IMPL(TypeName, _UNWRAP(ElementTuples))

#define _ENUM_NAME(TypeName) TypeName##_Kind
#define _MAKE_ENUM(TypeName, ElementTuples)                                                        \
  typedef enum _ENUM_NAME(TypeName) { _GENERATE_ENUM_FIELDS(TypeName, ElementTuples) };

#define SUM(TypeName, ElementTuples)                                                               \
  _MAKE_ENUM(TypeName, ElementTuples)                                                              \
  typedef union TypeName##_Data {                                                                  \
    _EXPAND_UNION_ARGS(ElementTuples)                                                              \
  };                                                                                               \
  typedef struct TypeName {                                                                        \
    enum _ENUM_NAME(TypeName) kind;                                                                \
    enum TypeName##_Data data;                                                                     \
  }

#endif
