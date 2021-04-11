#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int iscalled = 0;

void CpuProfiler(clock_t *clk)
{
    /*
    It takes a pointer to a variable of type clock_t. It then stores the current cpuCount into this variable. A second call passing back the value
    of the pointer to the function subtracts the previous cpu count from then current clock count into this variable and stores it back into the passed value;
    The problem with this method is that the clock count for the cpu is independent of whether your process is executing or not. Due to interrupts your process can be removed from the running state 
    a context switch to higher priority process or i/o process, therefore measured clock counts might not accurately depict the running time for your functions.
    */   
    if(!iscalled)
    {
        iscalled = 1;
        *clk = clock();
    } else {
        iscalled = 0;
        *clk = clock() - *clk;
    }
}

int sumSquares1(int n)
{
    return (n*((2*n) + 1)*(n + 1))/6;
}

int sumSquares2(int n)
{
    int sum = 0;
    for(int i = 1; i <= n; i++)
    {
        sum += (int) pow(i,2);
    }
    return sum;
}

int main()
{

    clock_t c,ck;
    CpuProfiler(&c);
    printf("sum1 = %d",sumSquares1(20000));
    CpuProfiler(&c);

    CpuProfiler(&ck);
    sumSquares2(20000);
    CpuProfiler(&ck);

    printf("Clock ticks for sumSquare1 is  %ld and that for sumSquares2 is %ld",c,ck);
}