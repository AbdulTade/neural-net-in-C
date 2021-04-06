#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define __compare_fn_t __COMPAR_FN_T

typedef int int32;
typedef long int int64;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef float float32;
typedef double float64;

/* struct node {
	float64 *weights;
	float64 bias;
};

struct layer {
	struct node *nodes;
	uint32 node_len;
};

struct network {
	struct layer *layers;
	uint32 layer_len;
};  */

struct Vector {
    float64 *data;
    uint32 length;
};

struct Matrix {
    float64 **matData;
    uint32 *shape;
};

struct Matrix mProduct(struct Matrix mat1,struct Matrix mat2)
{
    int32 isMul = (mat1.shape[1] == mat2.shape[0]) ? 1 : 0;
    uint32 rows = mat1.shape[0];
    uint32 columns = mat2.shape[1];
    struct Matrix retMat;
    retMat.shape[0] = rows;
    retMat.shape[1] = columns;
    float64 **data = (float64 **)calloc(rows,sizeof(float64 *));
    if(isMul)
    {
        
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                for(int k = 0; k < mat1.shape[1]; k++)
                {
                    data[i][j] += mat1.matData[i][k] * mat2.matData[k][j];
                }
            }
        }
        
    } else {
        perror("Cannot multiply two matrices of unequal dimensions\n");
        exit(EXIT_FAILURE);
    }
    retMat.matData = data;
    return retMat;
}

struct Matrix identity(uint32 dim)
{
    struct Matrix obj;
    float64 **data = (float64 **) calloc(dim,sizeof(float64 *));
    obj.shape[0] = dim;
    obj.shape[1] = dim;
    for(int k = 0; k < dim; k++)
    {
        for(int j = 0; j < dim; j++)
        {
            if(j == k)
            {
                data[k][j] = 1;
                continue;
            }
            data[k][j] = 0;
        }
    }
    obj.matData = data;
    return obj;
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
    int32 index = vector.length;
    if(vector.length%2 == 0)
    {
        return 0.5*(vector.data[index/2] + vector.data[(index/2)+1]);
    }
    return vector.data[(int32)(index/2)];
}

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

float64 mode(struct Vector vector)
{
    qsort(vector.data,vector.length,sizeof(float64),comparator);
}
