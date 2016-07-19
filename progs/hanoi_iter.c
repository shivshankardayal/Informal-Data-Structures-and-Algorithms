#include <stdio.h>
#include <stdlib.h> // for malloc
#include <limits.h> // for UINT_MIN
#include <math.h> // for calculating total no. of moves

// we create a stack of disks
typedef struct stack {
  // used for creating stack
  int capacity;
  // top of stack
  int top;
  // contiguous array to hold disks
   int* array;
}stackT;

stackT* create_stack( int capacity)
{
  stackT* s = (stackT*)malloc(sizeof(stackT));
  
  s->capacity = capacity;
  s->top = -1;
  s->array = ( int*)malloc(sizeof(int)*s->capacity);

  return s;
}

// obviously stack is full when top is the last element
int is_full(stackT* s)
{
  return (s->top == s->capacity - 1);
}

// same as full stack is empty if top is -1
int is_empty(stackT* s)
{
  return (s->top == -1);
}

// push an element to stack increasing top
void push(stackT* s, int element)
{
  if (is_full(s))
    return;
  s->array[++s->top] = element;
}

// pop an element from stack
 int pop(stackT* s)
{
  if (is_empty(s))
    return INT_MIN;
  return s->array[s->top--];
}

void move_disks(stackT* left, stackT* right, char l, char r)
{
   int l_disk = pop(left);
   int r_disk = pop(right);

  // When l is empty
  if (l_disk == INT_MIN)
  {
    push(left, r_disk);
    printf("Move the disk %d from \'%c\' to \'%c\'\n", r_disk, r, l);
  }

  // When r is empty
  else if (r_disk == INT_MIN)
  {
    push(right, l_disk);
    printf("Move the disk %d from \'%c\' to \'%c\'\n", l_disk, l, r);
  }

  // When top disk of l > top disk of r
  else if (l_disk > r_disk)
  {
    push(left, l_disk);
    push(left, r_disk);
    printf("Move the disk %d from \'%c\' to \'%c\'\n", r_disk, r, l);
  }  

  // When top disk of l < top disk of r
  else
  {
    push(right, r_disk);
    push(right, l_disk);
    printf("Move the disk %d from \'%c\' to \'%c\'\n", l_disk, l, r);
  }
}

// implement core logic
void hanoi_iter( int n, stackT* left, stackT* mid, stackT* right)
{
   long i, total_moves;
  char l = 'L', r = 'R', m = 'M';

  // if no. of disks is even then we need to swap M and R
  if(n % 2 == 0) {
    char temp = r;
    r = m;
    m = temp;
  }

  total_moves = pow(2, n) - 1;
  // obviously larger no. represent larger disks to they will
  // be pushed first
  for(i = n; i >= 1; i--) {
    push(left, i);
  }

  for(i = 1; i <= total_moves; ++i) {
    if(i % 3 == 1) {
      move_disks(left, right, l, r);
    } else if (i % 3 == 2) {
      move_disks(left, mid, l, m);
    } else if (i % 3 == 0) {
      move_disks(mid, right, m, r);
    }
  }
}

int main()
{
   int n = 0;
  
  printf("How many disks you want?\n");
  scanf("%d", &n);
 
  stackT *left, *mid, *right;
 
  // Create three stacks of size 'n'
  // to hold the disks
  left = create_stack(n);
  mid = create_stack(n);
  right = create_stack(n);
 
  hanoi_iter(n, left, mid, right);
  
  return 0;
}
