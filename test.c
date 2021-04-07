#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

