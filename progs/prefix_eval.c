// This program evaluates a small postfix expression
// made up of four simple operators and single digit
// numbers

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int i = 0;
const char *a = "+4 5";

int prefix_eval() {
  int x = 0;

  while (a[i] == ' ')
    i++;

  if (a[i] == '+')
  {
    i++;
    return prefix_eval() + prefix_eval();
  }

  if (a[i] == '*')
  {
    i++;
    return prefix_eval() * prefix_eval();
  }

  while ( (a[i] >= '0') && (a[i] <= '9'))
    x = 10*x + (a[i++]-'0');

  return x;
}

int main()
{
  printf("Result is %d\n", prefix_eval());
  
  return 0;
}
