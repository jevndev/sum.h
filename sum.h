#ifndef SUM_H
#define SUM_H

// Utilities
#define _NARGS_IMPL(A0, A1, A2, A3, N, ...) N
#define _NARGS(...) _NARGS_IMPL(__VA_ARGS__, 3, 2, 1, 0)

#define _UNWRAP_IMPL(...) __VA_ARGS__
#define _UNWRAP(A) _UNWRAP_IMPL A

#define _GET_TYPE_IMPL_2(Type, Name) Type
#define _GET_TYPE_IMPL(...) _GET_TYPE_IMPL_2(__VA_ARGS__)
#define _GET_TYPE(Tuple) _GET_TYPE_IMPL(_UNWRAP(Tuple))

#define _GET_NAME_IMPL_2(Type, Name) Name
#define _GET_NAME_IMPL(...) _GET_NAME_IMPL_2(__VA_ARGS__)
#define _GET_NAME(Tuple) _GET_NAME_IMPL(_UNWRAP(Tuple))

// TODO: Rename args so this isn't as confusing
#define _EXPAND_ENUM_ARG_IMPL_2(Name, ElementName) Name##_##ElementName
#define _EXPAND_ENUM_ARG_IMPL(Name, ElementName) _EXPAND_ENUM_ARG_IMPL_2(Name, ElementName)
#define _EXPAND_ENUM_ARG(Name, Arg) _EXPAND_ENUM_ARG_IMPL(Name, _GET_NAME(Arg))

// TODO: use generic expand idiom thing to make recursive
#define _EXPAND_ENUM_ARGS_0(Name, A0) _EXPAND_ENUM_ARG(Name, A0)
#define _EXPAND_ENUM_ARGS_1(Name, A0, ...)                                                         \
  _EXPAND_ENUM_ARG(Name, A0), _EXPAND_ENUM_ARGS_0(Name, __VA_ARGS__)
#define _EXPAND_ENUM_ARGS_2(Name, A0, ...)                                                         \
  _EXPAND_ENUM_ARG(Name, A0), _EXPAND_ENUM_ARGS_1(Name, __VA_ARGS__),
#define _EXPAND_ENUM_ARGS_3(Name, A0, ...)                                                         \
  _EXPAND_ENUM_ARG(Name, A0), _EXPAND_ENUM_ARGS_2(Name, __VA_ARGS__),

#define _GENERATE_ENUM_FIELDS_DISPATCH(Name, Count, ...)                                           \
  _EXPAND_ENUM_ARGS_##Count(Name, __VA_ARGS__)
#define _GENERATE_ENUM_FIELDS_EXPAND_NARGS(Name, Count, ...)                                       \
  _GENERATE_ENUM_FIELDS_DISPATCH(Name, Count, __VA_ARGS__)
#define _GENERATE_ENUM_FIELDS_IMPL(Name, ...)                                                      \
  _GENERATE_ENUM_FIELDS_EXPAND_NARGS(Name, _NARGS(__VA_ARGS__), __VA_ARGS__)

#define _GENERATE_ENUM_FIELDS(Name, Args) _GENERATE_ENUM_FIELDS_IMPL(Name, _UNWRAP(Args))
#define _EXPAND_UNION_ARGS(...) __VA_ARGS__

#define _MAKE_ENUM(Name, Args) typedef enum Name##_Kind{_GENERATE_ENUM_FIELDS(Name, Args)};

#define SUM(Name, Args)                                                                            \
  _MAKE_ENUM(Name, Args)                                                                           \
  typedef union Name##_Data {                                                                      \
    _EXPAND_UNION_ARGS(Args)                                                                       \
  };                                                                                               \
  typedef struct Name {                                                                            \
    enum Name##_Kind kind;                                                                         \
    enum Name##_Data data;                                                                         \
  }

#endif
