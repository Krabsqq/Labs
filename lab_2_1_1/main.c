#include <stdio.h>
#include <stdlib.h>

int main()
{
    double x,y;
    printf("Enter x:  ");
    scanf("%lf",&x);
    printf("x=%lf",x );
    if(x<5)
    {
        x=x*x;
    }
    else
    {
        x=x*x*x;
    }
    printf("\nx=%lf",x);
    return 0;

}
