#include "sum.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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

// clang-format on

int main() {
  struct Diagnostics_Result result;

  TEST("make simple enum", _MAKE_ENUM, (Foo, ((int, i), (char, c))),
       "typedef enum Foo_Kind{Foo_i, Foo_c};", &result);
  TEST("make enum with one arg", _MAKE_ENUM, (Foo, ((int, i))), "typedef enum Foo_Kind{Foo_i};",
       &result);
  TEST("make simple union", _MAKE_UNION, (Foo, ((int, i), (char, c))),
       "typedef union Foo_Data { int i; char c; };", &result);
  TEST("make union with one arg", _MAKE_UNION, (Foo, ((int, i))),
       "typedef union Foo_Data { int i; };", &result);
}
