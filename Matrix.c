#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mathUtils.h"
#include "Vector.h"


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

void setShape(struct Matrix *matrix,int32 rows,int32 cols)
{
    matrix -> shape = (int32 *) calloc(2,sizeof(int32));
    matrix -> shape[0] = rows;
    matrix -> shape[1] = cols;
}

struct Matrix transpose(struct Matrix matrix)
{ 
    static struct Matrix retMat;
    setShape(&retMat, matrix.shape[0], matrix.shape[1]);
    retMat.matData = MatrixTemplate(retMat.shape);
    for(int i = 0; i < matrix.shape[0]; i++)
    {
        for(int j = 0; j < matrix.shape[1]; j++)
        {
            retMat.matData[j][i] = matrix.matData[i][j];
        }
    }
    return retMat;
} 

struct Matrix mProduct(struct Matrix mat1,struct Matrix mat2)
{
    int32 isMul = (mat1.shape[1] == mat2.shape[0]) ? 1 : 0;
    int32 rows = mat1.shape[0];
    int32 columns = mat2.shape[1];
    struct Matrix retMat;
    setShape(&retMat,rows,columns);
    int retShape[] = {rows,columns};
    retMat.matData = MatrixTemplate(retShape);
    if(isMul)
    {
        
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                for(int k = 0; k < mat1.shape[1]; k++)
                {
                    retMat.matData[i][j] += mat1.matData[i][k] * mat2.matData[k][j];
                }
            }
        }
        
    } else {
        perror("Cannot multiply two matrices of unequal dimensions\n");
        exit(EXIT_FAILURE);
    }
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


int32 isSymmetric(struct Matrix matrix)
{
    int isSquare = (matrix.shape[0] == matrix.shape[1]) ? 1 : 0;
    if(!isSquare) {
        perror("Symmetric matrix cannot be rectangular");
        exit(0);
    }
    for(int i = 0; i < matrix.shape[0]; i++)
    {
        for(int j = 0; j < matrix.shape[1]; j++)
        {
            if(matrix.matData[i][j] != matrix.matData[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}

float64 trace(struct Matrix matrix)
{
    int32 sum = 0;
    if(matrix.shape[0] != matrix.shape[1])
    {
        perror("Trace undefined for rectangular matrices");
        exit(-1);
    }
    for(int i = 0; i < matrix.shape[0]; i++)
    {
        sum += matrix.matData[i][i];
    }

    return sum;
}


void showMatrix(struct Matrix matrix)
{
    for(int k = 0; k < matrix.shape[0]; k++)
    {
        for(int j = 0; j < matrix.shape[1]; j++)
        {
            if(j == matrix.shape[1]-1) { printf("%f\n",matrix.matData[k][j]); continue;}
            printf("%f  ",matrix.matData[k][j]);
        }
    }
}

struct Matrix slice(struct Matrix matrix,int32 *rowRange,int32 *colRange)
{
    struct Matrix retMat;
    int32 rows = (rowRange[1]-rowRange[0]+1);
    int32 cols = (colRange[1]-colRange[0]+1);
    int32 shape[] = {rows,cols};
    retMat.shape = (int32 *) calloc(2,sizeof(int32));
    retMat.shape = shape;
    retMat.matData = MatrixTemplate(shape);
    int32 rowState = (rowRange[0] >= 0 && rowRange[1] < matrix.shape[0]) ? 1 : 0;
    int32 colState = (colRange[0] >= 0 && colRange[1] < matrix.shape[1]) ? 1 : 0;
    if(rowState && colState)
    {
            for(int i = rowRange[0]; i <= rowRange[1]; i++)
            {
                for(int j = colRange[0]; j <= colRange[1]; j++)
                {
                    retMat.matData[i-rowRange[0]][j-colRange[0]] = matrix.matData[i][j];
                }
            }
    } else {
        perror("Cannot slice range exceeds matrix dimensions");
        exit(-1);
    }
    return retMat;
}

struct Matrix randMatrix(int32 *shape)
{
    srand(time(0));
    struct Matrix matrix;
    setShape(&matrix, shape[0], shape[1]);
    matrix.matData = MatrixTemplate(shape);
    
    for(int i = 0; i < shape[0]; i++)
    {
        for(int j = 0; j < shape[1]; j++)
        {
            matrix.matData[i][j] = (float64) ((float64)rand()/RAND_MAX);
        }
    }
    return matrix;
}

float64 mNorm(struct Matrix matrix)
{
    float64 sum = 0;
    for(int i = 0; i < matrix.shape[0]; i++)
    {
        for (int j = 0; j < matrix.shape[1]; j++)
        {

            sum += matrix.matData[i][j] * matrix.matData[i][j];

        }
        
    }
    return sqrt(sum);
}