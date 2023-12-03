all: secuencial

secuencial: secuencial.cpp
    g++ -std=c++11 -o secuencial secuencial.cpp `pkg-config --cflags --libs opencv`

clean:
    rm -f secuencial