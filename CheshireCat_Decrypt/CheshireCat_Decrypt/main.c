#include <stdio.h>
#include <stdlib.h>

char readPassword();

int main()
{
    readPassword();
}

char readPassword(){
   char *passd;
   printf( "Enter the password to unlock your PC :\n");
   passd = getchar( );

   return passd;
}
