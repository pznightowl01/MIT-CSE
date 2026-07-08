//Name : Princita Zina Miranda
//Section : SCE-C
//Roll no. C17, Reg. no. 220905115

// Q) Write a MPI program using N processes to find 1! +2! +.....+N!. Use scan. Also, handle different errors using error handling routines.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

void ErrorH(int err_code){
    if (err_code!=MPI_SUCCESS){
        char error_string[MPI_MAX_ERROR_STRING];
        int length, err_class;

        MPI_Error_class(err_code, &err_class);
        MPI_Error_string(err_code, error_string, &length);

        printf("MPI Error Class: %d\n", err_class);
        printf("MPI Error String: %s\n", error_string);
    }
}

int main(int argc, char *argv[]){
    int rank, size;
    int num, fact, sum;
    int err_code;

    err_code=MPI_Init(&argc, &argv);
    ErrorH(err_code);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    err_code=MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ErrorH(err_code);

    err_code=MPI_Comm_size(MPI_COMM_WORLD, &size);
    ErrorH(err_code);

    num=rank+1;

    err_code=MPI_Scan(&num,&fact,1, MPI_INT,MPI_PROD,MPI_COMM_WORLD);
    ErrorH(err_code);

    err_code=MPI_Scan(&fact,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    ErrorH(err_code);

    if(rank==size-1)
        printf("Sum of factorials from 1! to %d! = %d\n", size, sum);

    MPI_Finalize();
    return 0;
}
