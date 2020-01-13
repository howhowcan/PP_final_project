#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> 


long long N;
long long p,q,e;
long long phiN;

int main(int argc,char **argv)
{
	N=strtoul(argv[1],NULL,0);
	long long d=strtoul(argv[2],NULL,0);
	long long SQRTN = (long long)sqrt(N);
//	cout << "before" << endl;
//	cout << "first\n";
	p = q = 0;
//	#pragma omp parallel for
	for(long long i=1;i<=(SQRTN-1)/2;i++)
	{
		if(N%(2*i+1)==0)
		{
			p = 2*i+1;
			q = N/p;
		}
	}
//	cout << "fifth\n";
	phiN=(p-1)*(q-1);		

	#pragma omp parallel for
	for(unsigned long long j=2;j<phiN;j++)
	{
		if(d*j%phiN==1){
			e = j;
		}
	}

//	cout << "sixth\n";
	printf("%llu\n",e);

	
    return 0;
}
