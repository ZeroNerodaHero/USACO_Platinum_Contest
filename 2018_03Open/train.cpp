#include "grader.h"
#include <iostream>
using namespace std;
#define B 1024
#define F 4450
#define INF 1000000007

int min(int a, int b){
    return (a < b) ? a : b;
}

void helpBessie(int v)
{
    int N = getTrainLength();
    int K = getWindowLength();
    int i = getCurrentCarIndex();
    int p = getCurrentPassIndex();
    if(p == 0){
        if(i == 0){
            set(0,0);
            set(1,-1);
        }
        int f = get(0), e = get(1);
        if(i%B == 0 || (i >= K && (i-K)%B == 0)){
            while(e >= f && v <= get(2*e+3)) e--;
            e++;
            set(2*e+2,i);
            set(2*e+3,v);
        } else {
            int x = get(2*e+3);
            if(v <= x){
                e--;
                while(e >= f && v <= get(2*e+3)) e--;
                e++;
                set(2*e+2,i);
                set(2*e+3,v);
            }
        }
        if(i >= K-1 && (i-K+1)%B == 0){
            //while(e >= f && get(2*f+2) <= i+B-K) f++;
            while(e >= f && get(2*f+2) <= i-K) f++;
            set(F+(i-K+1)/B,get(2*f+2));
        }
        set(0,f);
        set(1,e);
    } else{
        if(i < get(F)) return;
        if(i == get(F)){
            set(0,0);
            set(1,-1);
            set(F-1,1);
            set(F-2,INF);
            set(F-3,0);
        }
        int f = get(0), e = get(1);
        int out = get(F-3), b = get(F-1);
        if((i - get(F+b-1)) <= B){
            while(e >= f && get(2*e+3) >= v) e--;
            e++;
            set(2*e+2,i);
            set(2*e+3,v);
        } else{
            int x = get(F-2);
            if(v < x){
                set(F-2,v);
            }
        }
        if((out + K - 1) == i){
            while(e >= f && get(2*f+2) < out) f++;
            shoutMinimum(min(get(F-2),get(2*f+3)));
            out++;
        }
        while(B*b+K-1 < N && get(F+b) == i){
            while(out <= B * b){
                while(e >= f && get(2*f+2) < out) f++;
                shoutMinimum(min(get(F-2),get(2*f+3)));
                out++;
            }
            b++;
            f = e = 0;
            set(2*e+2,i);
            set(2*e+3,v);
            set(F-2,INF);
        }
        set(0,f);
        set(1,e);
        set(F-3,out);
        set(F-1,b);

    }
    
}
