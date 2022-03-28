#include <iostream>
#include <fstream>
#include<cmath>
#include <chrono>
#include <vector>
#include "mkl_implementation.h"
#include <string>
#include "openblas_implementation.h"
# include "pthread_implementation.h"
using namespace std;

string cmdhelp() {
    string s1 = "ERROR: There was an error while parsing the command line argument \n";
    string suggest = "Do you need help with command line arguments? [Y/N] \n";
    cout << s1;
    cout << suggest;
    string ans;
    cin >> ans;
    if (ans == string("Y") || ans == string("y")) {
        string s2 = "\n HELP \n";
        string s3 = "--------------------------------------------- \n";
        string s4 = "Command line arguments MUST be of on of the following formats: \n";
        string s5 = "./yourcode.out mkl fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt \n";
        string s6 = "./yourcode.out openBlas fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt \n";
        string s7 = "./yourcode.out pthread fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt \n";
        string s = s2 + s3 + s4 + s5 + s6 + s7;
        return s;
    } else {
        string s = "\n";
        return s;
    }
}
// MAIN

int main(int argc, char *argv[]) {
    try
    {
    if (argc > 1) {
        if (argv[2] == string("fullyconnected") && argv[1] ==string("openBlas")) {
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            string input = argv[3];
            string weight = argv[4];
            string bias = argv[5];
            string output = argv[6];
            fullyConnectedOpenBlas(input,weight,bias,output);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Time taken : " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
            cout << "Done!" << endl;
        }
          else if (argv[2] == string("fullyconnected") && argv[1] ==string("mkl")) {
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            string input = argv[3];
            string weight = argv[4];
            string bias = argv[5];
            string output = argv[6];
            fullyConnectedMKL(input,weight,bias,output);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Time taken : " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
            cout << "Done!" << endl;
        }
          else if (argv[2] == string("fullyconnected") && argv[1] ==string("pthread")) {
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            string input = argv[3];
            string weight = argv[4];
            string bias = argv[5];
            string output = argv[6];
            flmatrix A = createMatrix(input);
            flmatrix B = createMatrix(weight);
            flmatrix C = createMatrix(bias);
            flmatrix res = mla(A,B,C);
            printMatrix3(res, output);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Time taken : " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
            cout << "Done!" << endl;
        } else {
          cout << cmdhelp();
        }
    } else {
      cout << cmdhelp();
    }
    }
catch (const char *excp)  
{
        cout << "ERROR: " << excp;
}
catch(string s)
{
    cout << s  ;
}

catch(...)
{
    cout << "Unknown error, please recheck files";  // to account for unknown errors
}
    return 0;
}