#include <bits/stdc++.h>

using namespace std; 

unsigned long long N;
unsigned long long p,q,e;

int main(int argc,char **argv)
{
	N=strtoul(argv[1],NULL,0);
	unsigned long long d=strtoul(argv[2],NULL,0);
	unsigned long long SQRTN = (unsigned long long)sqrt(N);
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

	for(unsigned long long j=2;j<phiN;j++)
	{
		if(d*j%phiN==1){
			e = j;
		}
	}
	

//	cout << "sixth\n";
	cout<<"e = "<<e<<endl;
	
    return 0;
}
