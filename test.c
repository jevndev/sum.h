#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#define SUM_H_STRIP_PREFIX
#include "sum.h"

#define STRINGIFY(...) #__VA_ARGS__
#define STRINGIFY_EXPANDED(...) STRINGIFY(__VA_ARGS__)
#define EXPAND_AND_STRINGIFY_OUTPUT(macro, ...) STRINGIFY_EXPANDED(macro __VA_ARGS__)

enum Diagnostics_Result_Kind { DIAGNOSTICS_RESULT_SUCCESS, DIAGNOSTICS_RESULT_MISMATCH };

struct Diagnostics_Result_Success {};
struct Diagnostics_Result_Mismatch {
  const char *result_begin;
  const char *expected_begin;
  const char *result_mismatch;
  const char *expected_mismatch;
};

union Diagnostics_Result_Data {
  struct Diagnostics_Result_Success success;
  struct Diagnostics_Result_Mismatch mismatch;
};

struct Diagnostics_Result {
  enum Diagnostics_Result_Kind kind;
  union Diagnostics_Result_Data data;
};

bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

bool matches_without_whitespace(const char *const result, const char *const expected_result,
                                struct Diagnostics_Result *const diagnostics) {

  const char *result_p = result;
  const char *expected_result_p = expected_result;

  while (!(*result_p == '\0' && *expected_result_p == '\0')) {
    while (is_whitespace(*result_p)) {
      result_p++;
    }

    while (is_whitespace(*expected_result_p)) {
      expected_result_p++;
    }

    if ((*result_p == '\0') != (*expected_result_p == '\0') || (*result_p != *expected_result_p)) {
      diagnostics->kind = DIAGNOSTICS_RESULT_MISMATCH;

      diagnostics->data.mismatch.result_begin = result;
      diagnostics->data.mismatch.result_mismatch = result_p;

      diagnostics->data.mismatch.expected_begin = expected_result;
      diagnostics->data.mismatch.expected_mismatch = expected_result_p;

      return false;
    }
    expected_result_p++;
    result_p++;
  }
  diagnostics->kind = DIAGNOSTICS_RESULT_SUCCESS;
  return true;
}

void print_result(const char *const test_name, const struct Diagnostics_Result *const result) {
  printf("%s: ", test_name);

  switch (result->kind) {
  case DIAGNOSTICS_RESULT_SUCCESS: {
    printf("\033[32m[SUCCESS]\033[0m\n");
  } break;
  case DIAGNOSTICS_RESULT_MISMATCH: {
    printf("\033[31m[FAILURE]\033[0m\n");
    // Print matching characters in yellow
    const char *expected_p = result->data.mismatch.expected_begin;
    const char *mismatch_pos = result->data.mismatch.expected_mismatch;

    printf("< \033[33m");
    while (expected_p < mismatch_pos) {
      printf("%c", *expected_p);
      expected_p++;
    }

    // Print mismatch character in red
    if (*mismatch_pos != '\0') {
      printf("\033[31m%c", *mismatch_pos);
      expected_p++;
    }

    // Print rest in yellow
    printf("\033[33m");
    while (*expected_p != '\0') {
      printf("%c", *expected_p);
      expected_p++;
    }

    printf("\033[0m\n");
    printf("> ");

    // Print matching characters in yellow
    const char *result_p = result->data.mismatch.result_begin;
    const char *result_mismatch_pos = result->data.mismatch.result_mismatch;

    printf("\033[33m");
    while (result_p < result_mismatch_pos) {
      printf("%c", *result_p);
      result_p++;
    }

    // Print mismatch character in red
    if (*result_mismatch_pos != '\0') {
      printf("\033[31m%c", *result_mismatch_pos);
      result_p++;
    }

    // Print rest in yellow
    printf("\033[33m");
    while (*result_p != '\0') {
      printf("%c", *result_p);
      result_p++;
    }

    printf("\033[0m\n");
  } break;
  }
}

// clang-format off
#define TEST(name, macro, input, expected_result, diagnostics)                 \
  do {                                                                         \
    matches_without_whitespace(                                                \
      EXPAND_AND_STRINGIFY_OUTPUT(macro,input),                                \
      expected_result,                                                         \
      diagnostics);                                                            \
    print_result(name, &result);                                               \
  } while (0)

#define TEST_UNSUPPORTED(name, macro, input, expected_result, diagnostics) \
  do { \
    printf("%s: \033[33m[UNSUPPORTED]\033[0m\n", name); \
  } while (0)

// clang-format on

int main() {
  struct Diagnostics_Result result;

  TEST("make simple enum", _SUM_H__MAKE_ENUM, (Foo, ((int, i), (char, c))),
       "typedef enum Foo_Kind{Foo_INVALID = 0 , Foo_i, Foo_c} Foo_Kind;", &result);
  TEST("make enum with one arg", _SUM_H__MAKE_ENUM, (Foo, ((int, i))),
       "typedef enum Foo_Kind{Foo_INVALID = 0 , Foo_i} Foo_Kind;", &result);

  // This works, but it's kinda useless because we can't generate sum types like this
  TEST("make enum with inline nontrivial type", _SUM_H__MAKE_ENUM,
       (Foo, ((typedef struct {int n}, i), (char, c))),
       "typedef enum Foo_Kind{Foo_INVALID = 0 , Foo_i, Foo_c} Foo_Kind;", &result);
  TEST("make enum with 16 args", _SUM_H__MAKE_ENUM,
       (Foo, ((int, a0), (char, a1), (float, a2), (double, a3), (short, a4), (long, a5),
              (unsigned int, a6), (unsigned char, a7), (unsigned short, a8), (unsigned long, a9),
              (signed char, a10), (long long, a11), (unsigned long long, a12), (void *, a13),
              (size_t, a14), (bool, a15))),
       "typedef enum Foo_Kind{Foo_INVALID = 0 , Foo_a0, Foo_a1, Foo_a2, Foo_a3, Foo_a4, "
       "Foo_a5,  Foo_a6, Foo_a7, Foo_a8, Foo_a9, Foo_a10, Foo_a11, Foo_a12, Foo_a13, "
       "Foo_a14, Foo_a15} Foo_Kind;",
       &result);

  TEST("make simple union", _SUM_H__MAKE_UNION, (Foo, ((int, i), (char, c))),
       "typedef union Foo_Data { int i; char c; } Foo_Data;", &result);
  TEST("make union with one arg", _SUM_H__MAKE_UNION, (Foo, ((int, i))),
       "typedef union Foo_Data { int i; } Foo_Data;", &result);
  //  This actually expands the bool macro, hence the check for _Bool below.
  TEST("make union with 16 args", _SUM_H__MAKE_UNION,
       (Foo, ((int, a0), (char, a1), (float, a2), (double, a3), (short, a4), (long, a5),
              (unsigned int, a6), (unsigned char, a7), (unsigned short, a8), (unsigned long, a9),
              (signed char, a10), (long long, a11), (unsigned long long, a12), (void *, a13),
              (size_t, a14), (bool, a15))),
       "typedef union Foo_Data { int a0; char a1; float a2; double a3; short a4; long a5; unsigned "
       "int a6; "
       "unsigned char a7; unsigned short a8; unsigned long a9; signed char a10; long long a11; "
       "unsigned "
       "long long a12; void* a13; size_t a14; _Bool a15; } Foo_Data;",
       &result);

  // TODO: make unions with inline nontrivial types supported.
  // We'd need to be smarter about where we put the type we pass to support this.
  //
  // That's a lot of work
  // Also putting typedefs out into the global scope on behalf of the user feels a little *too*
  // magic
  TEST_UNSUPPORTED("make union with inline nontrivial type", _SUM_H__MAKE_UNION,
                   (Foo, ((typedef struct MyData{int n}, i), (char, c))),
                   "typedef struct MyData{int n} MyData; typedef union Foo_Data { struct MyData i; "
                   "char c; } Foo_Data;",
                   &result);

  TEST("make simple struct", _SUM_H__MAKE_STRUCT, (Foo, ((int, i), (char, c))),
       "typedef struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo", &result);
  TEST("make struct with one arg", _SUM_H__MAKE_STRUCT, (Foo, ((int, i))),
       "typedef struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo", &result);
  TEST("make struct with inline nontrivial type", _SUM_H__MAKE_STRUCT,
       (Foo, ((typedef struct {int n}, i), (char, c))),
       "typedef struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo", &result);
  TEST("make struct with 16 args", _SUM_H__MAKE_STRUCT,
       (Foo, ((int, a0), (char, a1), (float, a2), (double, a3), (short, a4), (long, a5),
              (unsigned int, a6), (unsigned char, a7), (unsigned short, a8), (unsigned long, a9),
              (signed char, a10), (long long, a11), (unsigned long long, a12), (void *, a13),
              (size_t, a14), (bool, a15))),
       "typedef struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo", &result);

  TEST("make simple sum type", SUM, (Foo, ((int, i), (char, c))),
       "typedef enum Foo_Kind { Foo_INVALID = 0 , Foo_i, Foo_c } Foo_Kind; typedef union Foo_Data "
       "{ int "
       "i; char c; } "
       "Foo_Data; typedef "
       "struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo",
       &result);
  TEST("make sum type with one arg", SUM, (Foo, ((int, i))),
       "typedef enum Foo_Kind { Foo_INVALID = 0 , Foo_i } Foo_Kind; typedef union Foo_Data { int "
       "i; } "
       "Foo_Data; "
       "typedef struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo",
       &result);
  TEST("make sum with 16 args", SUM,
       (Foo, ((int, a0), (char, a1), (float, a2), (double, a3), (short, a4), (long, a5),
              (unsigned int, a6), (unsigned char, a7), (unsigned short, a8), (unsigned long, a9),
              (signed char, a10), (long long, a11), (unsigned long long, a12), (void *, a13),
              (size_t, a14), (bool, a15))),
       "typedef enum Foo_Kind { Foo_INVALID = 0, Foo_a0, Foo_a1, Foo_a2, Foo_a3, Foo_a4, Foo_a5, "
       "Foo_a6, Foo_a7, Foo_a8, Foo_a9, Foo_a10, Foo_a11, Foo_a12, Foo_a13, Foo_a14, Foo_a15 } "
       "Foo_Kind; "
       "typedef union Foo_Data { int a0; char a1; float a2; double a3; short a4; long a5; "
       "unsigned int a6; unsigned char a7; unsigned short a8; unsigned long a9; signed char a10; "
       "long long a11; unsigned long long a12; void* a13; size_t a14; _Bool a15; } Foo_Data; "
       "typedef struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo",
       &result);

  // see "make union with inline nontrivial type"
  TEST_UNSUPPORTED("make sum type with inline nontrivial type", SUM,
                   (Foo, ((typedef struct MyData{int n}, i), (char, c))),
                   "typedef enum Foo_Kind { Foo_INVALID = 0, Foo_i, Foo_c } Foo_Kind; typedef "
                   "struct MyData{int n} "
                   "MyData; typedef "
                   "union Foo_Data { struct MyData i; char c; } Foo_Data;; typedef "
                   "struct Foo { enum Foo_Kind kind; union Foo_Data data; } Foo",
                   &result);
}
