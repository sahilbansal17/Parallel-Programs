# Parallel Programming using Open MP / MPI

## Open MP
1. [Hello World](Open%20MP/Hello%20World/helloWorld.cpp)

		$ g++ -fopenmp -o hello helloWorld.cpp
		$ ./hello

2. [Matrix multiplication](Open%20MP/Matrix%20Multiplication/matrixMultiplication.cpp)

		$ g++ -fopenmp -o mul matrixMultiplication.cpp
		$ ./mul

## MPI

### Installation
1. [MPICH2](https://researchweb.iiit.ac.in/~abu_saad/files/Installing_MPI.pdf)
2. [Open MPI](https://github.com/firemodels/fds/wiki/Installing-Open-MPI-on-a-Linux-Cluster)

### Tutorials
[MPI Tutorials](https://mpitutorial.com)

### Programs

1. [Hello World](MPI/Hello%20World/mpi_hello_world.c)

		$ mpicc -o hello mpi_hello_world.cpp
		$ mpiexec -np 4 ./hello

2. [Using MPI Send and Receive](MPI/Send%20Receive/snd_rcv.c)

		$ mpicc -o snd_rcv snd_rcv.c
		$ mpiexec -np 4 ./snd_rcv