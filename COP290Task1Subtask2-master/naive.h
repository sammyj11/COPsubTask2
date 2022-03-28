#include <iostream>
#include <fstream>
#include<cmath>
#include <vector>
#include <string>
using namespace std;
#define fl float;
typedef vector<vector<float>> flmatrix;
typedef vector<float> flarray;

// FUNCTIONS 
flmatrix naiveMatrixMult(flmatrix A, flmatrix B) {
    int nrowsf = A.size();
    int ntmp = A[0].size();
    int ncolsf = B[0].size();

    flmatrix result(nrowsf, vector<float>(ncolsf, 0));

    for (int i = 0; i < nrowsf; i++)
    {
        for (int j = 0; j < ncolsf; j++)
        {
            float temp = 0;
            for (int k = 0; k < ntmp; k++)
            {
                temp += A[i][k]*B[k][j];
            }
            result[i][j] = temp;
        }    
    }
    return result;
}

flmatrix matrixAdd2(flmatrix C, flmatrix D) {
    int nrowsf = C.size();
    int ncolsf = C[0].size();

    flmatrix result(nrowsf, vector<float>(ncolsf, 0));

    for (int i = 0; i < nrowsf; i++)
    {
        for (int j = 0; j < ncolsf; j++)
        {
            result[i][j] = C[i][j] + D[i][j];
        }    
    }
    return result;
}

flmatrix naivemla(flmatrix M0, flmatrix M1, flmatrix bias) {
    flmatrix M2 = naiveMatrixMult(M0,M1);
    flmatrix res = matrixAdd2(M2,bias);
    return res;
}