#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mathUtils.h"
#include "Matrix.h"
#include "Vector.h"

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





int main()
{

    clock_t clk;
    CpuProfiler(&clk);
    struct Matrix matrix;
    int32 rows = 2;
    int32 cols = 5;
    int32 shape[] = {rows,cols};
    float64 **data = MatrixTemplate(shape);
    float64 r1[] =  {1,2,3,4,5};
    matrix.shape = (int32 *) calloc(2,sizeof(int32));
    matrix.shape[0] = rows;
    matrix.shape[1] = cols;
    //float64 r2[] =  {1,2,3,4,5};
    data[0] = r1;
    data[1] = r1;
    struct Matrix id = identity(5);
    showMatrix(id);
    CpuProfiler(&clk);
    printf("It took %ld clock ticks to run the file ",clk);
    return 0;

}
