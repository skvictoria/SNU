#include <stdio.h>
#include "roman.h"
#include "romanutil.h"
#include "tfdef.h"
#include "chrutil.h"


int is_roman(char c)
/*  This function is given a character and returns true if it is
        a valid roman numeral, flase otherwise.  */
{
    /*  convert digit to upper  */
    c = to_upper(c);
    /*  test the digit  */
    switch (c)
    {
    case 'M':
    case 'D':
    case 'C':
    case 'L':
    case 'X':
    case 'V':
    case 'I':  return TRUE;
    default:  return FALSE;
    }
}



int convert_roman(char c)
/*  This function is given a roman numeral and returns its value.
        NULL is returned if the character is not valid  */
{
    int digit;

    /*  convert digit to upper  */
    c = to_upper(c);
    /*  convert the digit  */
    switch (c)
    {
    case 'M':
        digit = M;
        break;
    case 'D':
        digit = D;
        break;
    case 'C':
        digit = C;
        break;
    case 'L':
        digit = L;
        break;
    case 'X':
        digit = X;
        break;
    case 'V':
        digit = V;
        break;
    case 'I':
        digit = I;
        break;
    default:
        digit = (int)NULL;
    }

    /*  and return its value  */
    return digit;
}


char to_upper(char c)
{
    if (IS_LOWER(c)) return c - 'a' + 'A';
    return c;
}
