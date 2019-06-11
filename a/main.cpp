#include <iostream>

using namespace std;

int main() {
    long long l,r,a,b,c,d;
    cin >> l >> r >> a;
    b=(r-l+1)%a;
    c=a-b;
    d=(r-l+1)/a ;
    cout << b*d*(d+1)/2+c*d*(d-1)/2;
    return 0;
}