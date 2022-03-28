#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include<cmath>
#include <vector>
#include <string>
#include <pthread.h>
using namespace std;
#define fl float;
typedef vector<vector<float>> flmatrix;
typedef vector<float> flarray;

int nr1, nc1, nr2, nc2;
flmatrix M1;
flmatrix M2;
flmatrix M3;

/*  ERROR MESSAGES */

string checkInput(string filename) {
    string check = "Please check the following input file: " + filename + "\n";
    return check;
}

string notInt() {
    string notInt = "ERROR: The dimensions of the matrix/vector must be an integer.\n";
    return notInt;
}

string notFloat() { 
    string s1 = "ERROR: An error occurred while constructing the matrix from input files. \n";
    string s2 = "POSSIBLE REASONS: \n";
    string s3 = "1. Dimensions do not match no. of elements provided. \n";
    string s4 = "2. Inputs are not floats. \n";
    return s1+s2+s3+s4;
}

string wrongDimAdd() {
    string s1 = "ERROR: Dimensions incompatible for matrix addition. Please check input files. \n";
    return s1;
}

string wrongDimMul() {
    string s1 = "ERROR: Dimensions incompatible for matrix multiplication. Please check input files. \n";
    return s1;
}

string fileError(string filename) {
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

/* Function Implementations */

flmatrix createMatrix(string filename) {
    int ncols;
    int nrows;

    // Give error if unable to open file 
    ifstream mfile (filename);
    if (mfile.fail()) {
        cout << fileError(filename);
        exit(0);
    }

    // Set nrows and ncols from the input file 
    // If not integers then give error

    mfile >> ncols;
    if (mfile.fail()) {
        cout << notInt();
        cout << checkInput(filename);
        exit(0);
    }

    mfile >> nrows;
    if (mfile.fail()) {
        cout << notInt();
        cout << checkInput(filename);
        exit(0);
    }

    // Initialize the matrix
    flmatrix matrix(nrows, vector<float>(ncols, 0));

    for (int i = 0; i < ncols; i++)
    {
        for (int j = 0; j < nrows; j++)
        {
            // Assign the values from the file to the matrix elements
            // If not floats then give error
            float mem;
            mfile >> mem; 
            if (mfile.fail()){ 
                cout << notFloat();
                cout << checkInput(filename);
                exit(0);
            }
            matrix[j][i] = mem;
        }
    }
    mfile.close();
    return matrix;
}

// Global structure containing an int argument rows
struct args {
    int rows;
};

// Helper function to help in multithreaded multiplication
// Multiplies a single row of M1 with all columns of M2
void *multRow(void *input) {    
    int r = ((struct args*)input)->rows;
    for (int j = 0; j < M2[0].size(); j++) {
        for (int i = 0; i < M1[0].size(); i++) {
            M3[r][j] += (M1[r][i] * M2[i][j]);    
        }
    }   
    pthread_exit(0);
}

// Matrix Multiplication implementation using pthreads
flmatrix pMatrMultiply(flmatrix A, flmatrix B) {
    int nrowsf = A.size();
    int ntmp = A[0].size();
    int ncolsf = B[0].size();

    // If n cols in A != n rows in B
    // Give error and exit
    if (ntmp != B.size()) {
        cout << wrongDimMul();
        exit(0);
    }

    flmatrix C(nrowsf, vector<float>(ncolsf, 0));  
    M1 = A;
    M2 = B;
    M3 = C;

    // Initialize the number of threads
    // Currently initialized to 3
    // Can be increased/decreased based on number of cores avl.
    int n_threads = 3;   
    pthread_t threads[n_threads];                 

    int i = 0; //Stores the base row br 
    while (i < (nrowsf-(n_threads-1)) {
        // Multiply br,br+1,..br+(n_threads-1) rows
        // with M2 in this step 
        // Parallely using multiple threads
        for (int j = 0; j < n_threads; j++) {
            struct args *input = (struct args *)malloc(sizeof(struct args));
            input->rows = i+j; // Current row number
            // Create thread corresponding to the row
            int t = pthread_create(&threads[j], NULL, multRow, (void *)input);
        }
        for (int k = 0; k < n_threads; k++) {
            void* status;
            // On completion of computation join the threads
            int t = pthread_join(threads[k], &status);
        }
        i = i+3;
    }

    // If nrows is not a multiple of n_threads
    // Take care of the corner cases
    int d = (nrowsf%n_threads);
    for (int j = 0; j < d; j++) {
        struct args *input = (struct args *)malloc(sizeof(struct args));
        input->rows = i+j;
        int t = pthread_create(&threads[j], NULL, multRow, (void *)input);
    }
    for (int k = 0; k < d; k++) {
        void* status;
        int t = pthread_join(threads[k], &status);
    }
    // Assign the output matrix
    C = M3;
    return C;
}

flmatrix matrixAdd(flmatrix C, flmatrix D) {
    int nrowsf = C.size();
    int ncolsf = C[0].size();

    // Check if sizes are compatible for addition
    if (nrowsf != D.size() || ncolsf != D[0].size()) {
        cout << wrongDimAdd();
        exit(0);
    }

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

flmatrix mla(flmatrix M0, flmatrix M1, flmatrix bias) {
    // Compute the fully connected layer
    flmatrix M2 = pMatrMultiply(M0,M1);
    flmatrix res = matrixAdd(M2,bias);
    return res;
}

void printMatrix3(flmatrix M, string filename) {
    int ncols = M[0].size();
    int nrows = M.size();

    ofstream mfile (filename);
    mfile << ncols << "\n";
    mfile << nrows << "\n";

    //Setting the elements of the matrix
    for (int i = 0; i < ncols; i++)
    {
        for (int j = 0; j < nrows; j++)
        {
            float mem = M[j][i];
            mfile << mem << "\n";
        }
    }
    mfile.close();
}
