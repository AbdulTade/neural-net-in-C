#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int int32;
typedef long int int64;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef float float32;
typedef double float64;

struct Vector {
    float64 *data;
    uint32 length;
};

struct Set {
    float64 *data;
    int32 length;
};

struct Counter {
    float64 *data;
    int32 *counts;
    int32 datalen;
};




int comparator(void *p,void *q)
{
    float64 *x = (float64 *) p;
    float64 *y = (float64 *) q;
    if(*x > *y)
    {
        return -1;
    }  else if(*x < *y)
    {
        return 1;
    } 
    
    return 0;
}


float64 vsum(struct Vector vector)
{
    float64 sum = 0;
    for(int k = 0; k < vector.length; k++)
    {
        sum += vector.data[k];
    }
    return sum;
}




struct Counter getUniqueElements(double *arr,int len)
{

    struct Counter counter;
    int32 *counts = (int32 *) calloc(len,sizeof(float64)); // initialize needed variables
    float64 count = 1;
    float64 *uniqueItems = (float64 *) calloc(len,sizeof(double));
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

struct Set createSet(struct Vector vector)
{
    struct Set set;
    int32 length = 1;
    float64 *data = (float64 *) calloc(vector.length,sizeof(float64));
    set.data = getUniqueElements(vector.data, vector.length).data;
    set.length = vector.length;
    return set;
}



struct Vector vpow(struct Vector vector,int num)
{
    struct Vector v;
    v.length = vector.length;
    v.data = (float64 *) calloc(vector.length,sizeof(float64));
    for(int k = 0; k < vector.length; k++)
    {
        v.data[k] = pow(vector.data[k],num);
    }
    return v;
}

struct Vector exponent(struct Vector vector,int num)
{
    struct Vector v;
    v.length = vector.length;
    v.data = (float64 *) calloc(vector.length,sizeof(float64));
    for(int k = 0; k < vector.length; k++)
    {
        v.data[k] = pow(num,vector.data[k]);
    }
    return v;
}

struct Vector vsin(struct Vector arg)
{
    struct Vector sines;
    //struct Vector v;
    sines.length = arg.length;
    sines.data = (float64 *) calloc(arg.length,sizeof(float64));
    for(int k = 0; k < arg.length; k++)
    {
        sines.data[k] = sin(arg.data[k]);
    }
    return sines;
    
}

struct Vector vcos(struct Vector arg)
{
     struct Vector cosines;
    cosines.length = arg.length;
    cosines.data = (float64 *) calloc(arg.length,sizeof(float64));
    for(int k = 0; k < arg.length; k++)
    {
        cosines.data[k] = cos(arg.data[k]);
    }
    return cosines;
}

float64 mean(struct Vector vector)
{
    float64 sum = 0;
    for(int i = 0; i < vector.length; i++)
    {
        sum += vector.data[i];
    }
    return sum/((float64)vector.length);
}

float64 median(struct Vector vector)
{
    qsort(vector.data,vector.length,sizeof(float64),comparator);
    int32 index = vector.length;
    if(vector.length%2 == 0)
    {
        return 0.5*(vector.data[index/2] + vector.data[(index/2)+1]);
    }
    return vector.data[(int32)(index/2)];
}

float64 modulus(struct Vector vector)
{
    float64 sum = 0;
    for(int i = 0; i < vector.length; i++)
    {
        sum += pow(vector.data[i],2);
    }
    return sqrt(sum);
}


float64 norm(struct Vector vector,double p)
{
    if(p == 0) {return (float64)vector.length; }
    else if(p == 1) { return vsum(vector); }
    float64 sum = 0;
    for(int k = 0; k < vector.length; k++)
    {
        sum += pow(vector.data[k],p);
    }
    return pow(sum,1/p);
}
