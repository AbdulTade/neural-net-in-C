#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int iscalled = 0;
struct Counter {
    double *data;
    int *counts;
    int datalen;
};

struct Polynomial {
    double *coeff;
    char var;
    int length;
};

struct Fraction {
    long int num;
    long int den;
    long int whole;
};

// struct cputime_t {

//     clock_t clk;
//     unsigned long long overflows;

// };

int comparator(void *,void *);
struct Counter getUniqueElements(double *,int );
struct Polynomial createPolynomial(double *,char,int);
void DispPoly(struct Polynomial polynomial);

int main()
{
    double arr[] = {3,5,2,5,0,1,2.8,9,2,5,1,1,5};
    int length = 13;
    //double *retArr = (double *) calloc(length,sizeof(double));
    struct Counter counter = getUniqueElements(arr,length);
    printf("Unique element is %d",counter.counts[5]);
    struct Polynomial polynomial = createPolynomial(arr,'y',length);
    DispPoly(polynomial);
}

int comparator(void *p,void *q)
{
    double *x = (double *) p;
    double *y = (double *) q;
    if(*x > *y)
    {
        return 1;
    }  else if(*x < *y)
    {
        return -1;
    } 
    
    return 0;
}

struct Counter getUniqueElements(double *arr,int len)
{

    struct Counter counter;
    int *counts = (int *) calloc(len,sizeof(double)); // initialize needed variables
    int count = 1;
    double *uniqueItems = (double *) calloc(len,sizeof(double));
    int countPos = 0;

    qsort(arr,len,sizeof(double),comparator); // sort elements so that counting is easy
    double item = arr[0];

    for(int k = 1; k < len ; k++)
    {
        if(arr[k] == item)
        {
            count += 1;
        } else {
            counts[countPos] = count;
            uniqueItems[countPos] = item;
            countPos += 1;
            count = 1;
            item = arr[k];
        }
    }
    // Populate struct variables with obtained data
    counter.data = uniqueItems;
    counter.counts = counts;
    counter.datalen = len;

    return counter;
}

struct Polynomial createPolynomial(double *coefficients,char var,int len)
{
    struct Polynomial polynomial;
    polynomial.coeff = coefficients;
    polynomial.length = len;
    polynomial.var = var;
    return polynomial;
}

void DispPoly(struct Polynomial polynomial)
{
    char *term = (char *) calloc(polynomial.length*polynomial.length,sizeof(double));
    int index = 0;
    int pos = 0;
    char *string = (char *) calloc(polynomial.length*polynomial.length,sizeof(double));
    for(int j = 0; j < polynomial.length; j++)
    {
        sprintf(term,"%f*%c^%d",polynomial.coeff[j],polynomial.var,polynomial.length-1-j);
        for(int k = index; k < strlen(term); k++)
        {
            string[j+pos] = term[k];
            pos += 1;
            if(k == strlen(term)-1)
            {
                
                index += strlen(term)+1;
                string[index-1] = '+';
            }
        }
    }
    printf("%s",string);
}

// char *strAdd(char *val1,char *val2,int len1,int len2)
// {
//     int carry = 0;
//     int len = (len1 >= len2 ) ? len2 : len1;
//     int biglen = (len1 >= len2) ? len1 : len2;
//     char *strSum = (char *) malloc(len * sizeof(char));
//     for(int  i = len-1; i >= 0; i--)
//     {
//         int c1 = val1[i] + val2[i] + carry;
//         if(c1 >= 106)
//         {
//             carry = 1;
//         } else { carry = 0; }
//         // if(i == 0)
//         // {
//         //     strSum[] = (char) ( 48 +  ((c1%48)%10) );
//         // } else {
        
//         strSum[i] = (char) ( 48 +  ((c1%48)%10) );

//         //}
//     }
// }   
 
// char *timeStr(struct cputime_t cputime)
// {
//     char * str = (char *) malloc(21 * cputime.overflows * sizeof(char));

// }

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

