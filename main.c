#include <stdio.h>
#include <stdlib.h>

#define UD_TYPE L
#include "uni_deque.h"

int PrintLongCallback(void *data, void *user_parameter)
{
  printf("%s %ld\n", (char *)user_parameter, *(long *)data);
  return 1;
}

// The UD_TYPE macro was defined to hold L and thus, the macros used wrap the specialized functions for type long.
void ExampleLong(void)
{
  ud_t deque = OPEN();
  if (deque == NULL)
    exit(1);

  PUSH_BACK(deque, 1);
  PUSH_FRONT(deque, 0);
  INSERT(deque, 1u, 2);
  PUSH_FRONT(deque, 5);
  PUSH_BACK(deque, 3);

  puts("~~~~~~~~~~~~~ forward");
  FOR_EACH(deque, 0u, SIZE(deque), PrintLongCallback, (void *)"++");
  puts("~~~~~~~~~~~~~ backward");
  FOR_EACH(deque, SIZE(deque) - 1u, 0 - SIZE(deque), PrintLongCallback, (void *)"--");

  puts("~~~~~~~~~~~~~ ascending order");
  SORT_ASC(deque);
  FOR_EACH(deque, 0u, SIZE(deque), PrintLongCallback, (void *)"++");

  puts("~~~~~~~~~~~~~ insert 4 into sorted deque");
  printf("%s contain 4.\n", FIND(deque, 4) == UD_INVALID_IDX ? "Doesn't" : "Does");
  INSERT_ASC(deque, 4);
  printf("%s contain 4.\n", FIND(deque, 4) == UD_INVALID_IDX ? "Doesn't" : "Does");

  puts("~~~~~~~~~~~~~ pop front");
  for (int i = POP_FRONT(deque); FAILED(deque) == 0; i = POP_FRONT(deque))
    printf("%d\n", i);

  CLOSE(deque);
}


int PrintStrCallback(void *data, void *user_parameter)
{
  printf("%s %s\n", (char *)user_parameter, (char *)data);
  return 1;
}

// Regardless of the UD_TYPE macro, you still can use other types by calling the functions directly.
void ExampleStr(void)
{
  ud_t deque = UDOpen();
  if (deque == NULL)
    exit(1);

  UDPushBackStr(deque, "bbb");
  UDPushFrontStr(deque, "aaa");
  UDInsertStr(deque, 1u, "ccc");
  UDPushFrontStr(deque, "fff");
  UDPushBackStr(deque, "ddd");

  puts("~~~~~~~~~~~~~ forward");
  UDForEach(deque, 0u, UDSize(deque), PrintStrCallback, (void *)"++");
  puts("~~~~~~~~~~~~~ backward");
  UDForEach(deque, UDSize(deque) - 1u, 0 - UDSize(deque), PrintStrCallback, (void *)"--");

  puts("~~~~~~~~~~~~~ descending order");
  UDSortDescStr(deque);
  UDForEach(deque, 0u, UDSize(deque), PrintStrCallback, (void *)"++");

  puts("~~~~~~~~~~~~~ insert 'eee' into sorted deque");
  printf("%s contain 'eee'.\n", UDFindStr(deque, "eee") == UD_INVALID_IDX ? "Doesn't" : "Does");
  UDInsertDescStr(deque, "eee");
  printf("%s contain 'eee'.\n", UDFindStr(deque, "eee") == UD_INVALID_IDX ? "Doesn't" : "Does");

  puts("~~~~~~~~~~~~~ pop back");
  for (char *ptr = UDPopBackStr(deque); ptr != NULL; ptr = UDPopBackStr(deque))
  {
    printf("%s\n", ptr);
    UDDeleteData(deque, ptr);
  }

  UDClose(deque);
}


int main(void)
{
  ExampleLong();
  puts("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
  ExampleStr();
  puts("");
  return 0;
}
