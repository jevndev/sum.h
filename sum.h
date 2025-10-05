#ifndef SUM_H
#define SUM_H

// Utilities
#define _SUM_H__NARGS_IMPL(ElementTuple, A1, A2, A3, N, ...) N
#define _SUM_H__NARGS(...) _SUM_H__NARGS_IMPL(__VA_ARGS__, 3, 2, 1, 0)

#define _SUM_H__UNWRAP_IMPL(...) __VA_ARGS__
#define _SUM_H__UNWRAP(A) _SUM_H__UNWRAP_IMPL A

#define _SUM_H__GET_TYPE_IMPL_2(Type, Name) Type
#define _SUM_H__GET_TYPE_IMPL(...) _SUM_H__GET_TYPE_IMPL_2(__VA_ARGS__)
#define _SUM_H__GET_TYPE(Tuple) _SUM_H__GET_TYPE_IMPL(_SUM_H__UNWRAP(Tuple))

#define _SUM_H__GET_NAME_IMPL_2(Type, Name) Name
#define _SUM_H__GET_NAME_IMPL(...) _SUM_H__GET_NAME_IMPL_2(__VA_ARGS__)
#define _SUM_H__GET_NAME(Tuple) _SUM_H__GET_NAME_IMPL(_SUM_H__UNWRAP(Tuple))

// Enum Generation Code

#define _SUM_H__EXPAND_ENUM_ARG_IMPL_2(TypeName, ElementName) TypeName##_##ElementName
#define _SUM_H__EXPAND_ENUM_ARG_IMPL(TypeName, ElementName)                                        \
  _SUM_H__EXPAND_ENUM_ARG_IMPL_2(TypeName, ElementName)
#define _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple)                                            \
  _SUM_H__EXPAND_ENUM_ARG_IMPL(TypeName, _SUM_H__GET_NAME(ElementTuple))

// TODO: use generic expand idiom thing to make recursive
#define _SUM_H__EXPAND_ENUM_ARGS_0(TypeName, ElementTuple)                                         \
  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple)
#define _SUM_H__EXPAND_ENUM_ARGS_1(TypeName, ElementTuple, ...)                                    \
  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple), _SUM_H__EXPAND_ENUM_ARGS_0(TypeName, __VA_ARGS__)
#define _SUM_H__EXPAND_ENUM_ARGS_2(TypeName, ElementTuple, ...)                                    \
  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple),                                                 \
      _SUM_H__EXPAND_ENUM_ARGS_1(TypeName, __VA_ARGS__),
#define _SUM_H__EXPAND_ENUM_ARGS_3(TypeName, ElementTuple, ...)                                    \
  _SUM_H__EXPAND_ENUM_ARG(TypeName, ElementTuple),                                                 \
      _SUM_H__EXPAND_ENUM_ARGS_2(TypeName, __VA_ARGS__),

#define _SUM_H__GENERATE_ENUM_FIELDS_DISPATCH(TypeName, Count, ...)                                \
  _SUM_H__EXPAND_ENUM_ARGS_##Count(TypeName, __VA_ARGS__)
#define _SUM_H__GENERATE_ENUM_FIELDS_EXPAND_NARGS(TypeName, Count, ...)                            \
  _SUM_H__GENERATE_ENUM_FIELDS_DISPATCH(TypeName, Count, __VA_ARGS__)
#define _SUM_H__GENERATE_ENUM_FIELDS_IMPL(TypeName, ...)                                           \
  _SUM_H__GENERATE_ENUM_FIELDS_EXPAND_NARGS(TypeName, _SUM_H__NARGS(__VA_ARGS__), __VA_ARGS__)

#define _SUM_H__GENERATE_ENUM_FIELDS(TypeName, ElementTuples)                                      \
  _SUM_H__GENERATE_ENUM_FIELDS_IMPL(TypeName, _SUM_H__UNWRAP(ElementTuples))

#define _SUM_H__ENUM_NAME(TypeName) TypeName##_Kind
#define _SUM_H__MAKE_ENUM(TypeName, ElementTuples)                                                 \
  typedef enum _SUM_H__ENUM_NAME(TypeName) {                                                       \
    _SUM_H__GENERATE_ENUM_FIELDS(TypeName, ElementTuples)                                          \
  };

// Union Generation Code

#define _SUM_H__EXPAND_UNION_ARG_IMPL_2(ElementType, ElementName) ElementType ElementName
#define _SUM_H__EXPAND_UNION_ARG_IMPL(ElementType, ElementName)                                    \
  _SUM_H__EXPAND_UNION_ARG_IMPL_2(ElementType, ElementName)
#define _SUM_H__EXPAND_UNION_ARG_UNWRAP(Elements) _SUM_H__EXPAND_UNION_ARG_IMPL(Elements)
#define _SUM_H__EXPAND_UNION_ARG(ElementTuple)                                                     \
  _SUM_H__EXPAND_UNION_ARG_UNWRAP(_SUM_H__UNWRAP(ElementTuple))

#define _SUM_H__EXPAND_UNION_ARGS_0(ElementTuple) _SUM_H__EXPAND_UNION_ARG(ElementTuple);
#define _SUM_H__EXPAND_UNION_ARGS_1(ElementTuple, ...)                                             \
  _SUM_H__EXPAND_UNION_ARG(ElementTuple);                                                          \
  _SUM_H__EXPAND_UNION_ARGS_0(__VA_ARGS__)
#define _SUM_H__EXPAND_UNION_ARGS_2(ElementTuple, ...)                                             \
  _SUM_H__EXPAND_UNION_ARG(ElementTuple);                                                          \
  _SUM_H__EXPAND_UNION_ARGS_1(__VA_ARGS__);
#define _SUM_H__EXPAND_UNION_ARGS_3(ElementTuple, ...)                                             \
  _SUM_H__EXPAND_UNION_ARG(ElementTuple);                                                          \
  _SUM_H__EXPAND_UNION_ARGS_2(__VA_ARGS__);

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
  };

// Struct Generation

#define _SUM_H__MAKE_STRUCT(TypeName, ElementTuples)                                               \
  typedef struct TypeName {                                                                        \
    enum _SUM_H__ENUM_NAME(TypeName) kind;                                                         \
    union _SUM_H__UNION_NAME(TypeName) data;                                                       \
  }

#define SUM_H_SUM(TypeName, ElementTuples)                                                         \
  _SUM_H__MAKE_ENUM(TypeName, ElementTuples)                                                       \
  _SUM_H__MAKE_UNION(TypeName, ElementTuples)                                                      \
  _SUM_H__MAKE_STRUCT(TypeName, ElementTuples)

#ifdef SUM_H_STRIP_PREFIX
#define SUM SUM_H_SUM
#endif

#endif
