#include <iostream>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
#include <chrono>
#include <numeric>
#include <vector>
#include "mklImplement.h"
#include "openBlasFile.h"
#include "pthreads_stage2.h"
#include "naive.h" 
#include <string>
using namespace std;

int main() {
    ofstream w1file("newres1.txt");  //4 files to write size, mean and SD of each of the 4 implmentations(in order mkl, openBlas, naive and pthread)
    ofstream w2file("newres2.txt");
    ofstream w3file("newres3.txt");
    ofstream w4file("newres4.txt");

    w1file << "#100\t90\t80\t70\t60\t50\t40\t30\t20\t10" << endl;
    w2file << "#100\t90\t80\t70\t60\t50\t40\t30\t20\t10" << endl;
    w3file << "#100\t90\t80\t70\t60\t50\t40\t30\t20\t10" << endl;
    w4file << "#100\t90\t80\t70\t60\t50\t40\t30\t20\t10" << endl;

<<<<<<< HEAD
    for (int j=0; j<100; j++) {
        for (int i = 1; i < 11; i++) {
            string idx = std::to_string(i);
            string input = "t" + idx + ".m1.txt";
            string weight = "t" + idx + ".m2.txt";
            string bias = "t" + idx + ".m3.txt";
            string output = "t" + idx + ".output.txt";
            
=======
        string idx = std::to_string(i);
        string input = "t" + idx + ".m1.txt";
        string weight = "t" + idx + ".m2.txt";
        string bias = "t" + idx + ".m3.txt";
        string output = "t" + idx + ".output.txt";
        
        for (int j=0; j<10; j++) {
>>>>>>> 01dd38c6c66ce7815ffa8283d2b0cab39597e2db
            chrono::steady_clock::time_point begin = chrono::steady_clock::now();           //chrono used as it has high time precision
            fullyConnectedOpenBlas(input,weight,bias,output);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            w1file << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "\t";
            
            chrono::steady_clock::time_point begin1 = chrono::steady_clock::now();
            fullyConnectedMKL(input,weight,bias,output);
            chrono::steady_clock::time_point end1 = chrono::steady_clock::now();
            w2file << chrono::duration_cast<chrono::microseconds>(end1 - begin1).count() << "\t";

            chrono::steady_clock::time_point begin3 = chrono::steady_clock::now();
            flmatrix P = createMatrix(input);
            flmatrix Q = createMatrix(weight);
            flmatrix R = createMatrix(bias);
            flmatrix res2 = naivemla(P,Q,R);
            printMatrix3(res2, output);
            chrono::steady_clock::time_point end3 = chrono::steady_clock::now();
            w3file << chrono::duration_cast<chrono::microseconds>(end3 - begin3).count() << "\t";

            chrono::steady_clock::time_point begin2 = chrono::steady_clock::now();
            flmatrix A = createMatrix(input);
            flmatrix B = createMatrix(weight);
            flmatrix C = createMatrix(bias);
            flmatrix res = mla(A,B,C);
            printMatrix3(res, output);
            chrono::steady_clock::time_point end2 = chrono::steady_clock::now();
            w4file << chrono::duration_cast<chrono::microseconds>(end2 - begin2).count() << "\t";
        }
<<<<<<< HEAD
    w1file << endl;
    w2file << endl;
    w3file << endl;
    w4file << endl;
=======
        
        double sum1 = std::accumulate(v1.begin(), v1.end(), 0.0);
        double mean1 = sum1 / v1.size();
        double sq_sum1 = std::inner_product(v1.begin(), v1.end(), v1.begin(), 0.0);
        double stdev1 = std::sqrt((sq_sum1 / v1.size()) - (mean1 * mean1));
        w1file << idx << "\t" << mean1 << "\t" << stdev1 << "\t";              //print size of matrix(if idx is 10 then since we assumed square matrices, it will print 10X10), mean and SD

        double sum2 = std::accumulate(v2.begin(), v2.end(), 0.0);
        double mean2 = sum2 / v2.size();
        double sq_sum2 = std::inner_product(v2.begin(), v2.end(), v2.begin(), 0.0);
        double stdev2 = std::sqrt((sq_sum2 / v2.size()) - (mean2 * mean2));
        w2file << idx << "\t" << mean2 << "\t" << stdev2 << "\t";

        double sum3 = std::accumulate(v3.begin(), v3.end(), 0.0);
        double mean3 = sum3 / v3.size();
        double sq_sum3 = std::inner_product(v3.begin(), v3.end(), v3.begin(), 0.0);
        double stdev3 = std::sqrt((sq_sum3 / v3.size()) - (mean3 * mean3));
        w3file << idx << "\t" << mean3 << "\t" << stdev3 << "\t";

        double sum4 = std::accumulate(v4.begin(), v4.end(), 0.0);
        double mean4 = sum4 / v4.size();
        double sq_sum4 = std::inner_product(v4.begin(), v4.end(), v4.begin(), 0.0);
        double stdev4 = std::sqrt((sq_sum4/v4.size()) - (mean4 * mean4));
        w4file << idx << "\t" << mean4 << "\t" << stdev4 << endl;
>>>>>>> 01dd38c6c66ce7815ffa8283d2b0cab39597e2db
    }
    w1file.close();
    w2file.close();
    w3file.close();
    w4file.close();
    cout << "DONE!" << endl;
    return 0;
}
    
