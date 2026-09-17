#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, data[5];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        // Initialize data
        for (int i = 0; i < 5; i++)
            data[i] = i * 10;

        printf("Process 0 sending data...\n");

        MPI_Send(data, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
        // Receive data
        MPI_Recv(data, 5, MPI_INT, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Process 1 received: ");

        for (int i = 0; i < 5; i++)
            printf("%d ", data[i]);

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
