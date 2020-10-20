#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
   void goodbye(void);
   int rc;
 
   rc = atexit(goodbye);
   printf("%d\n", rc);
   if (rc != 0)
      perror("Error in atexit");
   exit(0);
}
 
void goodbye(void)
   /* This function is called at normal program end */
{
   printf("The function goodbye was called at program end\n");
}
 
/****************  Output should be similar to:  ******************
 
The function goodbye was called at program end
*/
