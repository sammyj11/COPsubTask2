********************************************
COP290 TASK 1
Subtask 2

TEAM MEMBERS:
Samyak Jain (2020CS50667)
Viraj Agashe (2020CS10567)
********************************************

**********************
General Information 
**********************

The subtask-2 involves three implementations of the computation of a fully-connected 
layer. 

The three implementations are:
1. Basic Implementation optimized with multithreading (pthreads)
2. Implementation using INTEL-MKL
3. Implementation using OpenBLAS

The objective is to compare the three implementations for performance. Each of the three
inputs can be called from the command line. 

COMPILATION INSTRUCTIONS
-------------------------------------------
Compile the cpp file by writing 'make' in the command line.
However before doing so, change the path of mkl and openBlas set by us in the gcc command.
You can find the path of your mkl and openBlas through the whereis command on linux.
Type in whereis mkl, copy the path and replace it with the path provided by us in command.
Repeat above setp  for openBls with command whereis libopenblas
(the path is /usr/include/mkl for mkl and /usr/lib/x86_64-linux-gnu/libopenblas.a 
    /usr/lib/x86_64-linux-gnu/libopenblas.so for openBlas)

Alternatively, you need to type the following in the command line:

    g++ -I /usr/include/mkl -I /usr/lib/x86_64-linux-gnu/libopenblas.a 
    /usr/lib/x86_64-linux-gnu/libopenblas.so main.cpp -o ./yourcode.out 
    -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread 
    -lpthread -lm -ldl -pthread

Note that this must be done in the same directory containing the main.cpp file.

FULLY CONNECTED LAYER 
----------------------------------------------
Fully connected takes the inputs as an input matrix A (pxq), a weight matrix B (qxr),
a bias matrix C (pxr) and computes 
            M = AB + C

****************************
Using the Implementations
****************************

Once the ./yourcode.out file has been generated, the fully connected layer function 
may be called from the command line by using the following general command:

./yourcode.out <impl> fullyconnected <inputmatrix> <weightmatrix> <biasmatrix> <outputmatrix> 

Here, <impl> is a placeholder which may be replaced by: 
1. pthread - For the multithreaded implementation
2. mkl - For the INTEL-MKL implementation
3. openBlas - For the openBLAS implementation

The matrix placeholders are .txt files containing no. of cols, no. of rows and 
the elements of the matrix in column major order with one element per line. 

A sample command line argument would be:
.yourcode.out mkl fullyconnected a.txt b.txt c.txt o.txt

NOTE: 
------
1. Ideally, outputmatrix.txt should be an EMPTY text file before passing it to the function.
2. If outputmatrix.txt does not exist, it will create a new file of the same name. 
3. If outputmatrix.txt already exists, the function will OVERRIDE it. 
4. The time taken by each implementation is printed in the command line. 

**********************
Packages Used
**********************
The following packages are expected to be installed in the user's system:
1. INTEL-MKL
2. OpenBLAS
3. GNUPlot

The commands for installing them on a Linux-based system are as follows:
    sudo apt-get install intel-mkl
    sudo apt-get install libopenblas-dev
    sudo apt-get install gnuplot

**********************
Developer Information
**********************
Note: This section assumes that the reader has reasonable experience with programming in C++. 
Those who are unfamiliar with it are advised to ignore this section. 

Changing n_threads for faster pthread implementation
------------------------------------------------------
In the source code for the program, a variable local to the method "pMatrMultiply"
named "n_threads" is specified inside it's scope. 

The default value of this global variable is 3. However, for a faster implementation, 
the informed user may prefer to alter this value. 

We recommend keeping the number of threads <= no of cores in the processor of your machine
for optimal implementation. So, the user may increase this value if there are more cores of 
the processor available for the computation, or vice-versa, decrease it.

We do NOT recommend modifying any other portion of the source code of this subtask. 


**********************
Using GNUPLOT script
**********************
We have given a GNUPLOT script with a .p format. We have also given a python file for generating different matrices to test our implmenetations.
tester.cpp will use these newly generated files and chrono to plot tables after running these matrices for 100 iterations to calculate  time taken for each  matrix of different
size to run over different implmentations. We put these 100 values for each size in a column and for the purpose of our testing we have taken 10 different sizes, hence each file
has 10 columns. Overall there are 4 such files, one for each implementation. We have shown plots for sqaure matrices with size going from 10X10 to 100X100. Once these 4 files
have been formed, we can use the gnuplot script(just change the name of the file each time inside script(default set to data1.txt)) to make the 4 boxplots with error bars as
desired

********************************************************************************
