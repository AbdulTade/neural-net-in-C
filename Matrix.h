#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int int32;
typedef long int int64;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef float float32;
typedef double float64;

extern struct Matrix {
    float64 **matData;
    int32 *shape;
};
extern float64 **MatrixTemplate(int32 *shape);
extern struct Matrix transpose(struct Matrix matrix);
extern struct Matrix mProduct(struct Matrix mat1,struct Matrix mat2);
extern struct Matrix identity(int32 dim);
extern void showMatrix(struct Matrix matrix);
extern int32 isSymmetric(struct Matrix matrix);
extern int32 trace(struct Matrix matrix);
extern struct Matrix slice(struct Matrix matrix,int32 *rowRange,int32 *colRange);
