#include <stdio.h>
#include "INTALs.c"

int main() {
  char *num1 = initializeINTAL();
  char *num2 = initializeINTAL();

  printf("Enter the first INTAL number: ");
  gets(num1);

  printf("Enter the second INTAL number: ");
  gets(num2);

  printf("\nThe sum of the given INTAL numbers is: %s", INTALadder(num1, num2));

  printf("\nThe difference between the given INTAL numbers is: %s", INTALsubtractor(num1, num2));

  printf("\nThe multiplication of the given INTAL numbers is: %s", INTALmultiplicator(num1, num2));

  free(num1);
  free(num2);

  unsigned int n;
  printf("\nEnter the value of n: ");
  scanf("%u", &n);

  printf("\nThe given fibonacci INTAL is: %s", INTALfibonacci(n));

  unsigned int m;
  printf("\nEnter the value of m: ");
  scanf("%u", &m);

  printf("\nThe INTAL factorial of the given number is: %s", INTALfactorial(m));

  return 0;
}