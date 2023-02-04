#include<stdio.h>







float add(float a)
{
    printf("kayna\n");
}

double add(float a, int b)
{
    printf("kayna\n");
}

int main()
{
    add(3);
    add(8.9);
    add(8.9, 3);
}