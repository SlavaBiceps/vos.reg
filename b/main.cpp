#include <iostream>
#include <stdlib.h>

using namespace std;

long long k,j,res=0;

void ss(long long i,long long j){
    if (i*j==k){
        long long a=(j-a)/2;
        long long b=(i+j)/2;
        if (a>=0&&b>=0&&b<res){
            res=b;
        }
    }
}

int main() {
    cin >> k;
    for (long long i=0;i*i<abs(k);i++){
        if (k%i==0){
            j=abs(k)/i;
            if (i%2==j%2){
                ss(i,k);
                ss(i,-k);
                ss(-i,k);
                ss(-i,-k);
                ss(k,i);
                ss(k,-i);
                ss(-k,i);
                ss(-k,-i);

            }
        }
    }
    return 0;
}