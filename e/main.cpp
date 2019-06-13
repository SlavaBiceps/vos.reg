#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main() {
    int a,b,c;
    cin >> a >> b >> c;
    int f=(a+c-1)/c*c;
    int t=b/c*c;
    if (f>t) {
        cout << (b-a+1)/2 << endl;
        return 0;
    }
    int ans=(f-a)/2+(b-t)/2+1;
    f++;
    t++;
    if (c%2==0) {
        ans+=(t-f)/2;
    } else {
        ans+=(t-f)/c*((c+1)/2);
    }
    cout << ans << endl;
    return 0;
}

