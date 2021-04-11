#include <stdio.h>
#include <stdlib.h>

typedef int int32;
typedef long int int64;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef float float32;
typedef double float64;

extern struct Vector {
    float64 *data;
    uint32 length;
};

extern struct Set {
    float64 *data;
    int32 length;
};

extern struct Counter {
    float64 *data;
    int32 *counts;
    int32 datalen;
};

int comparator(void *p,void *q);
float64 vsum(struct Vector vector);
struct Counter getUniqueElements(double *arr,int len);
struct Set createSet(struct Vector vector);
struct Vector vpow(struct Vector vector,int num);
struct Counter getUniqueElements(double *arr,int len);
struct Vector exponent(struct Vector vector,int num);
struct Vector vsin(struct Vector arg);
struct Vector vcos(struct Vector arg);
float64 mean(struct Vector vector);
float64 median(struct Vector vector);
float64 modulus(struct Vector vector);
float64 norm(struct Vector vector,double p);