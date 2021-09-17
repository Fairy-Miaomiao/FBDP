#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"
int main(int argc, char** argv)
{
        int myid,numprocs;
        int N=0;
        double inte,local=0.0;
        MPI_Status status;
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
        --numprocs;
        if(myid==0)
        {
                printf("Please Enter N:\n");
                fflush(stdout);
                scanf("%d",&N);
        }
        MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        if(myid!=0)
        {
        for(int i=myid;i<N;i=i+numprocs)
        {
                local=local+sqrt(i*(i+1));
        }
        }
        MPI_Reduce(&local,&inte,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
        if(myid==0)
        {
                printf("The SqrtSum of data[%d] is %f\n",N,inte);
        }
        MPI_Finalize();
}
