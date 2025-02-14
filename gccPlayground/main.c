#include <stdio.h>
/*
gcc module.c -o module.o -c
ar r library.a module.o

gcc main.c -o main.o -c
gcc -o prog main.o module.o
*/

// define function from other module
int magicNumber();

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    magicNumber();
    return 0;
}
