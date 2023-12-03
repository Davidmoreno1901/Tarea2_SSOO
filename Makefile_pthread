all: pthread

pthread: pthread.cpp
    g++ -std=c++11 -o pthread pthread.cpp `pkg-config --cflags --libs opencv`

clean:
    rm -f pthread
