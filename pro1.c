#define a 10
#define b 100
#define N 100000000
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"
int main(int argc,char** argv)
{
        int myid,numprocs;
        double inte,x;
        double local=0.0;
        double sum=0.0;
        double dx=(double)(b-a)/N;
        MPI_Status status;
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD,&myid);
        MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
        --numprocs;
        if(myid==0)
        {
                for(int source=1;source<=numprocs;++source)
                {
                        MPI_Recv(&local,1,MPI_DOUBLE,source,99,MPI_COMM_WORLD,&status);
                        sum=sum+local;
                }
                printf("I am process %d. The sum is %f. \n",myid,sum);
        }
        else
        {
                for(int i=myid;i<N;i=i+numprocs)
                {
                        x=a+i*dx+dx/2;
                        local=local+x*x*x*dx;
                }
                printf("I am process %d. My local is %f. \n",myid,local);
                MPI_Send(&local,1,MPI_DOUBLE,0,99,MPI_COMM_WORLD);
        }
        MPI_Finalize();
}
