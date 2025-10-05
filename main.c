#include <malloc.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUM_H_STRIP_PREFIX
#include "sum.h"

typedef struct UserData {
  const char *name;
  size_t age;
} UserData;

void printUserData(const UserData data) {
  printf("Hi %s! You're %ld years old!\n", data.name, data.age);
}

typedef struct AdminData {
  size_t userCount;
} AdminData;

void printAdminData(const AdminData data) {
  printf("Hi Admin! There's %ld users now!\n", data.userCount);
}

SUM(LoginResult, ((UserData, user_login), (AdminData, admin_login), (size_t, remaining_tries)));

LoginResult try_submit_password(const char *const password, const size_t remaining_tries) {
  LoginResult result;

  if (strcmp(password, "correct-horse-battery-staple") == 0) {
    UserData user_data = {.name = "Randall", .age = 40u};
    result.kind = LoginResult_user_login;
    result.data.user_login = user_data;
    return result;
  } else if (strcmp(password, "admin") == 0) {
    AdminData admin_data = {.userCount = 1u};
    result.kind = LoginResult_admin_login;
    result.data.admin_login = admin_data;
    return result;
  } else {
    result.kind = LoginResult_remaining_tries;
    result.data.remaining_tries = remaining_tries - 1;
    return result;
  }
}

#define PASSWORD_BUFFER_SIZE 256

int doPasswordRepl(void) {
  size_t remaining_tries = 3;
  char password_buffer[PASSWORD_BUFFER_SIZE * sizeof(char)];

  while (remaining_tries != 0) {
    printf("\nEnter Password (%ld remaining attempts) >", remaining_tries);
    scanf("%s", password_buffer);

    LoginResult result = try_submit_password(password_buffer, remaining_tries);

    switch (result.kind) {
    case LoginResult_user_login:
      printUserData(result.data.user_login);
      return 0;
    case LoginResult_admin_login: {
      printAdminData(result.data.admin_login);
      return 0;
    }
    case LoginResult_remaining_tries: {
      remaining_tries = result.data.remaining_tries;
      break;
    }
    default:
      // should be unreachable!
    }
  };
  printf("\nToo many failed attempts! This incident will be reported\n");
  return 1;
}

int main() { return doPasswordRepl(); }
