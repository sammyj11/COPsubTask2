all:	main.cpp
	 g++ -I /usr/include/mkl -I /usr/lib/x86_64-linux-gnu/libopenblas.a /usr/lib/x86_64-linux-gnu/libopenblas.so main.cpp -o ./prog.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl -pthread
clean:
	$(RM)	yourcode.out