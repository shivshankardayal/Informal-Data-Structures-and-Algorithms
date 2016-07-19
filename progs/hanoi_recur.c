#include <stdio.h>

void move(int n, char left, char right, char mid)
{
  if(n > 0) {
    // move n-1 disks from left to mid
    move(n-1, left, mid, right);
    
    // move nth disk from left to right
    printf("Moved disk %d from left to right\n", n);

    // move n-1 disks from mid to right
    move(n-1, mid, left, right);
  }
}

int main()
{
  unsigned int n = 0;

  printf("How many disks you want to move?\n");
  scanf("%d", &n);

  move(n, 'L', 'R', 'C'); // L is left, R is right and C is center disk
  
  return 0;
}
