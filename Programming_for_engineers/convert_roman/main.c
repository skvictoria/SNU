#include <stdio.h>
#include "roman.h"

int main()
{
    int number;

    /*  prompt for first roman number entry  */
    printf("Enter an number in roman numerals(EOF to quit): ");

    /*  while there are more numbers  */
    while ((number = get_roman()) != EOF)
    {
        if (number > 0)
        {
            printf("The number is %d\n", number);
        }
            
        /* prompt for next number  */
        else
        {
            printf("Enter an number in roman numerals(EOF to quit): ");
        }
    }
    /*  clean up screen  */
    printf("\n");
}
