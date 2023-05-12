// Implement a recursive algorithm for computing the Fibonacci sequence using divide-and-conquer
#include<stdio.h>

int fib(int n) {
  if (n == 1)
    return 0; //First digit in the series is 0
  else if (n == 2)
    return 1; //Second digit in the series is 1
  else
    return (fib(n - 1) + fib(n - 2)); //Sum of previous two numbers in the series gives the next number in the series
}

int main() {
  int n = 10;
  int i;
  printf("The fibonacci series is :\n");
  for (i = 1; i <= n; i++) {
    printf("%d ", fib(i));
  }
}
