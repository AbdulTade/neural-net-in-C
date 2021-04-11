#include <stdio.h>
#include <stdlib.h>
#include "mathUtils.h"

typedef int int32;
typedef long int int64;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef float float32;
typedef double float64;

struct Matrix {
    float64 **matData;
    int32 *shape;
};

float64 **MatrixTemplate(int32 *shape)
{
    static float64 **matrix;
    matrix = calloc(shape[0],sizeof(float64 *));
    for(int i = 0; i < shape[0]; i++)
    {
        matrix[i] = (float64 *)calloc(shape[1],sizeof(float64));
    }
    return matrix;
}

void transpose(struct Matrix matrix)
{
    for(int i = 0; i < matrix.shape[0]; i++)
    {
        for(int j = 0; j < matrix.shape[1]; j++)
        {
            matrix.matData[j][i] = matrix.matData[i][j];
        }
    }
} 

struct Matrix mProduct(struct Matrix mat1,struct Matrix mat2)
{
    int32 isMul = (mat1.shape[1] == mat2.shape[0]) ? 1 : 0;
    int32 rows = mat1.shape[0];
    int32 columns = mat2.shape[1];
    struct Matrix retMat;
    retMat.shape[0] = rows;
    retMat.shape[1] = columns;
    retMat.shape = (int32 *) calloc(2,sizeof(int32));
    int retShape[] = {rows,columns};
    float64 **data = MatrixTemplate(retShape);
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

struct Matrix identity(int32 dim)
{
    struct Matrix obj;
    int32 shape[] = {dim,dim};
    float64 **data = MatrixTemplate(shape);
    obj.shape = (int32 *) calloc(2,sizeof(int32));
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

void showMatrix(struct Matrix matrix)
{
    for(int k = 0; k < matrix.shape[0]; k++)
    {
        for(int j = 0; j < matrix.shape[1]; j++)
        {
            if(j == matrix.shape[1]-1) { printf("%f\n",matrix.matData[k][j]); continue;}
            printf("%f\t",matrix.matData[k][j]);
        }
    }
}