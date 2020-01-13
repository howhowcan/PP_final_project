#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

unsigned long long N;
unsigned long long p,q;

int main(int argc,char **argv){
	N=strtoul(argv[1],NULL,0);
	unsigned long long d=strtoul(argv[2],NULL,0);

	MPI_Init(&argc, &argv);
	// Get the number of processes
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Get the rank of the process
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Status status;
//	printf("rank=%d\n",my_rank);
	unsigned long long SQRTN = (unsigned long long)sqrt(N)/2+1;
	unsigned long long l = SQRTN*my_rank/size, r = SQRTN*(my_rank+1)/size;
	p = q = 0;
//	printf("rank=%d, l=%lld, r=%lld\n",my_rank,l,r);
	for(unsigned long long i=l;i<r;i++){
		if(i!=0&&N%(i*2+1)==0){
			p = i*2+1;
			q = N/p;
		}
	}
//	printf("rank=%d, p=%lld, q=%lld\n",my_rank,p,q);
	if(my_rank!=0){
		unsigned long long tmp[2];
		tmp[0] = p;
		tmp[1] = q;
		MPI_Send(tmp,2,MPI_UNSIGNED_LONG_LONG,0,0,MPI_COMM_WORLD);
	}
	else{
		unsigned long long tmp[2];
		for(int i=1;i<size;i++){
			MPI_Recv(tmp,2,MPI_UNSIGNED_LONG_LONG,i,0,MPI_COMM_WORLD,&status);
			if(tmp[0]*tmp[1]==N)p = tmp[0], q = tmp[1];
		}
	}
	if(my_rank!=0){
		unsigned long long tmp[2];
		MPI_Recv(tmp,2,MPI_UNSIGNED_LONG_LONG,0,0,MPI_COMM_WORLD,&status);
		p = tmp[0];
		q = tmp[1];
	}
	else{
		unsigned long long tmp[2];
		tmp[0] = p;
		tmp[1] = q;
		for(int i=1;i<size;i++){
			MPI_Send(tmp,2,MPI_UNSIGNED_LONG_LONG,i,0,MPI_COMM_WORLD);
		}
	}
//	printf("rank=%d, p=%lld, q=%lld\n",my_rank,p,q);
	unsigned long long phiN=(p-1)*(q-1);
	unsigned long long e=0;
	l = phiN*my_rank/size, r = phiN*(my_rank+1)/size;
	for(unsigned long long j=l;j<r;j++){
		if(d*j%phiN==1){
			e = j;
		}
	}
	if(my_rank!=0){
		unsigned long long tmp[1];
		tmp[0] = e;
		MPI_Send(tmp,1,MPI_UNSIGNED_LONG_LONG,0,0,MPI_COMM_WORLD);
	}
	else{
		unsigned long long tmp[1];
		for(int i=1;i<size;i++){
			MPI_Recv(tmp,1,MPI_UNSIGNED_LONG_LONG,i,0,MPI_COMM_WORLD,&status);
			if(tmp[0])e = tmp[0];
		}
		printf("e = %lld\n",e);
	}
//	printf("rank=%d, e=%lld\n",my_rank,e);
  	MPI_Finalize();
	
    return 0;
}
