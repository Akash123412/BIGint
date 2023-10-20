#include <stdio.h>
#include <stdlib.h>
#include "functions.c"

int main()
{
	struct Node* num1 = inputbigint();
    struct Node* num2 = inputbigint();

    struct Node* sum = addbigint(num1, num2);
    
    struct Node* product = multiplybigint(num1, num2);

    struct Node* div = dividebigint(num1, num2);

    struct Node* diff = subtractbigint(num1, num2);


    // Print the results
    printf("Number 1: ");
    print(num1);
    printf("Number 2: ");
    print(num2);
    printf("Sum: ");
    print(sum);
    printf("Difference: ");
    print(diff);
    printf("Product: ");
    print(product);
    printf("Division: ");
    print(div);

    return 0;
}