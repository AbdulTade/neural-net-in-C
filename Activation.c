#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

struct Matrix BinaryStep(struct Matrix matrix)
{
    struct Matrix retMat;
    retMat.matData = MatrixTemplate(matrix.shape);
    retMat.shape = matrix.shape;
    
    for (int i = 0; i < matrix.shape[0]; i++)
    {
        for (int j = 0; j < matrix.shape[1]; j++)
        {
            
            retMat.matData[i][j] = (matrix.matData[i][j] > 0 ) ? 1 : 0;

        }
        
    }
    
    return retMat;
}

struct Matrix Sigmoid(struct Matrix matrix)
{
    struct Matrix retMat;
    retMat.matData = MatrixTemplate(matrix.shape);
    retMat.shape = matrix.shape;
    for (int i = 0; i < matrix.shape[0]; i++)
    {
        for (int j = 0; j < matrix.shape[1]; j++)
        {
            
            retMat.matData[i][j] = 1 / (1 + exp(-matrix.matData[i][j]));

        }
        
    }
    return retMat;
}