#include <bits/stdc++.h>
using namespace std;
 
const int MX=1000000;
int prime[MX];
int num_prime;
bool h[MX];
 
// normal prime sieve
void calPrime()
{
    for(int i=2;i<MX;i++) if(!h[i])
    {
        prime[num_prime++]=i;
        for(int j=i+i;j<MX;j+=i)
            h[j]=true;
    }
}
 
// Optimized
void calPrime2()
{
    for(int i=2;i<MX;i++) if(!h[i])
    {
        prime[num_prime++]=i;
        if(MX>(long long)i*i) for(int j=i*i;j<MX;j+=i)
            h[j]=true;
    }
}
 
// euler sieve
void calPrime3()
{
    for(int i=2;i<MX;i++)
    {
        if(!h[i]) prime[num_prime++]=i;
        for(int j=0;j<num_prime;j++)
        {
            if(i*prime[j]>MX) break;
            h[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
 
long long get_ticks()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec*1000000000LL + now.tv_nsec;

}

int main(int argc, char *argv[])
{
    long long ticks = get_ticks();
    //cout << ticks << endl;
    int c=1;
    if(argc > 1) {
        c = atoi(argv[1]);
    }
    cout << "Test for case " << c << endl;
    if(c ==1) calPrime();
    else if(c==2) calPrime2();
    else calPrime3();
    ticks = get_ticks()-ticks;
    cout << "Total number of primes: " << num_prime << endl;
    cout << ticks << endl;
}
