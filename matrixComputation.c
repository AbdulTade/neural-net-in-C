#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mathUtils.h"
#include "Matrix.h"
#include "Vector.h"


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
    float64 r1[] =  {1,2,3,4,5};
    matrix.shape = (int32 *) calloc(2,sizeof(int32));
    matrix.shape[0] = rows;
    matrix.shape[1] = cols; 
    //float64 r2[] =  {1,2,3,4,5};
    matrix.matData = MatrixTemplate(shape);
    matrix.matData[0] = r1;
    matrix.matData[1] = r1;
    struct Matrix id = identity(10);
    struct Matrix retMat = transpose(matrix);
    showMatrix(retMat);
    printf("\n");
    if(isSymmetric(matrix)) {printf("Yes it is");}
    showMatrix(matrix);
    CpuProfiler(&clk);
    printf("It took %ld clock ticks to run the file ",clk);
    return 0;

}
