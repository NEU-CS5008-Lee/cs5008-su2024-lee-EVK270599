// name: Kaustubha Eluri 
// email: eluri.k@northeastern.edu

#include<stdio.h>
#include <math.h>
int main()
{
    int a,b,c, choice;
    
    printf("Enter your choice\n");
    printf(" 1.addition\n 2. Subtraction\n 3. Multiplication\n 4. Division\n");
    scanf("%d",&choice);
    
    printf("Enter a and b values");
    scanf("%d %d", &a, &b);
    
    // Add your code here using switch

    switch(choice) {
        case 1:
            result = a + b;
            printf("Result of addition: %d\n", result);
            break;
        case 2:
            result = a - b;
            printf("Result of subtraction: %d\n", result);
            break;
        case 3:
            result = a * b;
            printf("Result of multiplication: %d\n", result);
            break;
        case 4:
            if (b != 0) {
                result = a / b;
                printf("Result of division: %d\n", result);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
             
    return 0;
}
