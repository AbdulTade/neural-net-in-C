#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

typedef void (*func)(struct Matrix *, struct Matrix *);

char *options[7] = {"binaryStep","sigmoid","tanh","ReLU","Softplus","LeakyReLU","Gaussian"};

void binStep(struct Matrix *matrix,struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            matrix -> matData[i][j] = (x > 0 ) ? 1 : 0;
        }
        
    }
}

void sigmoid(struct Matrix *matrix,struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            retMat -> matData[i][j] = 1 / (1 + exp(-x));
        }
        
    }
}

void ActTanh(struct Matrix *matrix,struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            retMat -> matData[i][j] = (1 - exp(-2*x)) / (1 + exp(-2*x));
        }
        
    }
}

void ReLU(struct Matrix *matrix,struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            matrix -> matData[i][j] = (x > 0) ? x : 0;
        }
        
    }
}

void Softplus(struct Matrix *matrix,struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            matrix -> matData[i][j] = log(1 + exp(x));
        }
        
    }
}

void LeakyReLU(struct Matrix *matrix, struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            matrix -> matData[i][j] = (x > 0) ? x : 0.01*x;
        }
        
    }
}

void Gaussian(struct Matrix *matrix,struct Matrix *retMat)
{
    float64 x = 0;
    for (int i = 0; i < matrix -> shape[0]; i++)
    {
        for (int j = 0; j < matrix -> shape[1]; j++)
        {
            x = matrix -> matData[i][j];
            matrix -> matData[i][j] = exp(-x);
        }
        
    }
}

void Activators(struct Matrix *matrix,struct Matrix *retMat,char *opt)
{

    func *funcs;
    funcs = calloc(7,sizeof(func));
    funcs[0] = &binStep;
    funcs[1] = &sigmoid;
    funcs[2] = &tanh;
    funcs[3] = &ReLU;
    funcs[4] = &Softplus;
    funcs[5] = &LeakyReLU;
    funcs[6] = &Gaussian;

    char *options[] =  {"binaryStep","sigmoid","tanh","ReLU","Softplus","LeakyReLU","Gaussian"};
    size_t max = strlen(opt);
    for(int i = 0; i < 7; i++)
    {
        if(!strncmp(opt,options[i],max))
        {
            funcs[i](matrix,retMat);
            break;
        }
    }
    char *msg = "string arg unrecognized";
    char optArr[256];
    snprintf(optArr,256,"%s\nValid options %s %s %s %s %s %s",msg,options[0],options[1],options[2],options[3],options[4],options[5]);
    perror(optArr);char *options[7] = {"binaryStep","sigmoid","tanh","ReLU","Softplus","LeakyReLU","Gaussian"};
}

// struct Matrix Activators(struct Matrix matrix,char *type,float64 alpha)
// {
//     struct Matrix retMat;
//     retMat.matData = MatrixTemplate(matrix.shape);
//     retMat.shape = matrix.shape;
//     float64 x = 0;
    
//     for (int i = 0; i < matrix.shape[0]; i++)
//     {
//         for (int j = 0; j < matrix.shape[1]; j++)
//         {
//             x = matrix.matData[i][j];
//             /*
//             Remove switch statement to reduce inefficiencies due to
//             checking switch for every iteration.
//             */
//             switch(intOpt(type))
//             {
//                 case 0:
//                     retMat.matData[i][j] = (x > 0 ) ? 1 : 0;
//                     break;
//                 case 1:
//                     retMat.matData[i][j] = 1 / (1 + exp(-x));
//                     break;
//                 case 2:
//                     retMat.matData[i][j] = (1 - exp(-2*x))/(1 + exp(-2*x));
//                     break;
//                 case 3:
//                     retMat.matData[i][j] = (x > 0) ? x : 0;
//                     break;
//                 case 4:
//                     retMat.matData[i][j] = log(1 + exp(x));
//                     break;
//                 case 5:
//                     retMat.matData[i][j] = (x > 0) ? x : 0.01*x;
//                     break;
//                 case 6:
//                     retMat.matData[i][j] = exp(-x*x);
//                 default:
//                     break;
//             }

//         }
        
//     }
    
//     return retMat;
// }

