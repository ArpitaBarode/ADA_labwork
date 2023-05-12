// Recursive function to calculate factorial of a number
unsigned long factorial(int n)
{
    // base case: if `n` is 0 or 1
    if (n < 1) {
        return 1;
    }
 
    // use the recurrence relation
    return n * factorial(n - 1);
}
 
int main()
{
    int n = 5;
    printf("The Factorial of %d is %lu", n, factorial(n));
 
    return 0;
}