#include <bits/stdc++.h>
#include <pthread.h>
#include <time.h>
using namespace std; 

unsigned long long N,d,num;
unsigned long long p,q,phiN;
unsigned long long e=0;
unsigned long long SQRTN;
int number_of_cpu;
int cnt1=0, cnt2=0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;



void* child(void* arg)
{
	pthread_mutex_lock( &mutex1 );
	int id=cnt2;
	cnt2++;
	pthread_mutex_unlock( &mutex1 );
	unsigned long long max=phiN/number_of_cpu;
	for(unsigned long long j=id*max;j<(id+1)*max;j++)
	{
		// cout << "j = " << j << "\n" ;
		if(d*j%phiN==1){
			pthread_mutex_lock( &mutex2 );
			e = j;
			pthread_mutex_unlock( &mutex2 );
		}	
//		cout << endl;
	}
	pthread_exit(NULL);
}


int main(int argc,char **argv)
{
	if(argc != 4) {
		cout << "usage: ./Pthreads <N> <D> <num of threads>\n";
		exit(1);
	}
	
	N=strtoul(argv[1],NULL,0);
	d=strtoul(argv[2],NULL,0);
	
//	cout << "first\n";
	SQRTN = (unsigned long long)sqrt(N);
//	cout << "second\n";
	pthread_t t;
//	cout << "third\n";
	number_of_cpu = atoi(argv[3]);
	// cout << "fourth\n";

	p = q = 0;
	for(unsigned long long i=1;2*i+1<=SQRTN;i++)
	{
		if(N%(2*i+1)==0)
		{
			p = 2*i+1;
			q = N/p;
		}
	}
	cout << "fifth\n";
	phiN=(p-1)*(q-1);	
	for(int i=0;i<number_of_cpu;i++)
    {
    	pthread_create(&t, NULL, child, NULL);	
	}
	for(int i=0;i<number_of_cpu;i++)
    {
    	pthread_join(t,NULL);
	}

	cout<<"e = "<<e<<"\n";
    return 0;
}
// g++ -pthread -std=c++11 -O2 -s Pthreads.cpp -o Pthreads