#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int iscalled  = 0;

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