# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# define THREAD_PER_BLOCK 1024

unsigned long long N;
unsigned long long p,q;
unsigned long long e_final[5];



__global__
void find_e(unsigned long long phiN, unsigned long long d, unsigned long long *e, unsigned long long step) {
    unsigned long long j = blockIdx.x * blockDim.x + threadIdx.x;
    j = j * step + 1;
    // if(j < 0)
    //     printf ("hello\n");
    // printf("j = %d\n", j);
    if(j == 1 || j >= phiN)
        return;
    // printf("%d ~ %d\n", j, j+step);
    for(unsigned long long i = j; i < j + step; ++i) {
        // printf("d*j = %llu\n", d*j);
        if(d*i%phiN==1){
            *e = i;
            // printf("succeed\n");
        }    
    }
    return;
    
}




int main(int argc,char **argv)
{
	N=strtoul(argv[1],NULL,0);
	unsigned long long d=strtoul(argv[2],NULL,0);
	unsigned long long SQRTN = (unsigned long long)sqrt(N);
	unsigned long long *e;
	unsigned long long step = 100000;

    if(argc == 2) {
        printf("usage: ./CUDA <N> <d>");
        exit(1);
    }
//	cout << "before" << endl;

//	cout << "first\n";
	p = q = 0;
	for(unsigned long long i=1;2*i+1<=SQRTN;i++)
	{
		if(N%(2*i+1)==0)
		{
			p = 2*i+1;
			q = N/p;
		}
	}
//	cout << "fifth\n";
	unsigned long long phiN=(p-1)*(q-1);
    printf("phiN = %llu\n", phiN);
    printf("block num = %llu\n", phiN/step + 1);


    cudaMalloc(&e, sizeof(unsigned long long)); 	
    e_final[0] = 0;
    cudaMemcpy(e, e_final, sizeof(unsigned long long), cudaMemcpyHostToDevice);

    // phiN = 100;
    // d = 3;
    find_e<<<(phiN/step + 1 + THREAD_PER_BLOCK - 1) / THREAD_PER_BLOCK, THREAD_PER_BLOCK>>>(phiN, d, e, step);

    cudaMemcpy(e_final, e, sizeof(unsigned long long), cudaMemcpyDeviceToHost);
	// for(unsigned long long j=2;j<phiN;j++)
	// {
	// 	if(d*j%phiN==1){
	// 		e = j;
	// 	}
	// }



//	cout << "sixth\n";
    printf("e = %llu\n", e_final[0]);

    // printf("finished\n");
	cudaFree(e);
    return 0;
}
