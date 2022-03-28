#pragma once
#include <iostream>
#include <fstream>
#include<cmath>
#include <chrono>
#include <vector>
#include "mkl.h"
#include <string>
#include "errors.h"
using namespace std;

/* ERROR MESSAGES */ 

string checkInput2(string filename) {
    string check = "Please check the following input file: " + filename + "\n";
    return check;
}

string notInt2() {
    string notInt2 = "ERROR: The dimensions of the matrix/vector must be an integer.\n";
    return notInt2;
}

string notFloat2() { 
    string s1 = "ERROR: An error occurred while constructing the matrix from input files. \n";
    string s2 = "POSSIBLE REASONS: \n";
    string s3 = "1. Dimensions do not match no. of elements provided. \n";
    string s4 = "2. Inputs are not floats. \n";
    return s1+s2+s3+s4;
}

string wrongDimMul2() {
    string s1 = "ERROR: Dimensions incompatible for matrix multiplication. Please check input files. \n";
    return s1;
}

string fileError2(string filename) {
    string suggestion;
    string s1 = "ERROR: There was an error opening the file. \n";
    if (filename.size()>4) {
        if (filename.substr(filename.size()-4) != string(".txt")) {
            suggestion = "Did you mean: " + filename + ".txt";
        }
    } else {
        suggestion = "The file " + filename + " may not exist.";
    }
    return s1 + suggestion;
}

/* FUNCTIONS */ 

void printMatrix2(float* M, string filename,int nrows, int ncols) {
    ofstream mfile (filename);
    mfile << ncols << "\n";
    mfile << nrows << "\n";

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++) {
            float mem = M[ncols*i+j];
            mfile << mem << "\n";
        }
    }
    mfile.close();
}

// Computation of fully connected layer using MKL

void fullyConnectedMKL(string f1, string f2, string f3, string f4) {
    int m, k, n, temp;
    float *A, *B, *C;

    // Check if file is valid
    ifstream mfile1 (f1);
    if (mfile1.fail()) {
        cout << fileError2(f1);
        exit(0);
    }
    
    // Check if nrows and ncols are integers
    // If not give error 
    mfile1 >> k;
    if (mfile1.fail()) {
        cout << notInt2();
        cout << checkInput2(f1);
        exit(0);
    }
    mfile1 >> m;
    if (mfile1.fail()) {
        cout << notInt2();
        cout << checkInput2(f1);
        exit(0);
    }

    A = (float *)mkl_malloc( m*k*sizeof( float ), 64 );

    // Set the elements of A
    for (int i = 0; i < m*k; i++)
    {
            float mem;
            mfile1 >> mem; 
            // If input elements are not floats
            // Give error
            if (mfile1.fail()){ 
                cout << notFloat2();
                cout << checkInput2(f1);
                exit(0);
            }

            A[i] = mem;
    }
    mfile1.close();

     // Check if file is valid
    ifstream mfile2 (f2);
    if (mfile2.fail()) {
        cout << fileError2(f2);
        exit(0);
    }

    // Check if nrows and ncols are integers
    // If not give error 
    mfile2 >> n;
    if (mfile2.fail()) {
        cout << notInt2();
        cout << checkInput2(f2);
        exit(0);
    }

    mfile2 >> temp;
    if (mfile2.fail()) {
        cout << notInt2();
        cout << checkInput2(f2);
        exit(0);
    }

    // Verify if dimensions suitable for matrix multiplication
    if (temp != k) {
        cout << wrongDimMul2();
        exit(0);
    }

    B = (float *)mkl_malloc( k*n*sizeof( float ), 64 );

    // Set the elements of B
    for (int i = 0; i < k*n; i++)
    {
            float mem;
            mfile2 >> mem; 
            // If input elements are not floats
            // Give error
            if (mfile2.fail()){ 
                cout << notFloat2();
                cout << checkInput2(f2);
                exit(0);
            }

            B[i] = mem;
    }
    mfile2.close();

     // Check if file is valid
    ifstream mfile3 (f3);
    if (mfile3.fail()) {
        cout << fileError2(f3);
        exit(0);
    }

    // Check if nrows and ncols are integers
    // If not give error 
    mfile3 >> n;
    if (mfile3.fail()) {
        cout << notInt2();
        cout << checkInput2(f3);
        exit(0);
    }

    mfile3 >> m;
    if (mfile3.fail()) {
        cout << notInt2();
        cout << checkInput2(f3);
        exit(0);
    }

    C = (float *)mkl_malloc( m*n*sizeof( float ), 64 );

    // Set the elements of C
    for (int i = 0; i < m*n; i++)
    {
            float mem;
            mfile3 >> mem; 
            // If input elements are not floats
            // Give error
            if (mfile3.fail()){ 
                cout << notFloat2();
                cout << checkInput2(f3);
                exit(0);
            }

            C[i] = mem;
    }
    mfile3.close();

    // Use sgemm functionality of MKL for float matrices (arrays)
    // Matrix is in column major order
    // No transpose needed 
    // Input matrix dimensions and constants alpha,beta = 1
    // Input matrices - A, B, C   
    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 
                m, n, k, 1, A, m, B, k, 1, C, m);
    // Print the output matrix into the output file
    printMatrix2(C,f4,m,n);
}

