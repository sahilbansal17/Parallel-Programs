/*
 * Reference used: https://github.com/wesleykendall/mpitutorial/blob/gh-pages/tutorials/mpi-send-and-receive/code/send_recv.c
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size < 2) {
        printf("World size must be greater than 1!\n");
        return 0;
    }

    int number;
    if (world_rank == 0) {
        number = -1;
        MPI_Send(
        /* data         = */ &number,
        /* count        = */ 1,
        /* datatype     = */ MPI_INT,
        /* destination  = */ 1,
        /* tag          = */ MPI_ANY_TAG,
        /* communicator = */ MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Status mpi_status;
        MPI_Recv(
        /* data         = */ &number,
        /* count        = */ 1,
        /* datatype     = */ MPI_INT,
        /* source       = */ 0,
        /* tag          = */ MPI_ANY_TAG,
        /* communicator = */ MPI_COMM_WORLD,
        /* status       = */ &mpi_status);
        printf("Process 1 received number %d from process 0\n", number);
    }
    MPI_Finalize();
    return 0;
}