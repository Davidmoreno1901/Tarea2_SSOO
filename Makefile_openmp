all: openmp

openmp: openmp.cpp
    g++ -std=c++11 -fopenmp -o openmp openmp.cpp `pkg-config --cflags --libs opencv`

clean:
    rm -f openmp
