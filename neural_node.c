#include <stdio.h>
#include <stdlib.h>

typedef int int32;
typedef long int int64;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef float float32;
typedef double float64;

struct node {
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
};

struct Matrix {
    float64 *(*matData);
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
    float64 data[mat1.shape[0]][mat2.shape[1]];
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
}

struct Matrix identity(uint32 dim)
{
    struct Matrix obj;
    float64 data[dim][dim];
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


int main()
{
    struct node n1,n2,n3;
    struct node n4,n5,n6;
    struct node n7,n8,n9;

    struct layer l1,l2,l3;
    float64 arr1 = {1,2,3,4,5};
    n1.weights;
    n1.bias = 0.45;
    return 0;
}
