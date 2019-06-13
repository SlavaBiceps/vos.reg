#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;

int up[5002][5002],dn[5002][5002],sumu[5002][5002],sumd[5002][5002];

int main(){
    int n,p,res=0;
    cin >> n >> p;
    for (int i=1;i<=n;i++){
        for (int j=1;j<i;j++){
            up[i][j]=0;
            if (i-j>j){
                up[i][j]=(sumd[i-j][i-j]-sumd[i-j][j])%mod;
            }
            dn[i][j]=sumu[i-j][j-1];

            sumu[i][j]=(sumu[i][j-1]+up[i][j])%mod;
            sumd[i][j]=(sumd[i][j-1]+dn[i][j])%mod;
        }
        up[i][i]=1;
        dn[i][i]=1;
        sumu[i][i]=(sumu[i][i-1]+up[i][i])%mod;
        sumd[i][i]=(sumd[i][i-1]+dn[i][i])%mod;
        for (int j=i+1;j<=n;j++){
            sumu[i][j]=sumu[i][i];
            sumd[i][j]=sumd[i][i];
        }
    }
    res=up[n][p];
    if (p!=n){
        res=(res+dn[n][p])%mod;
    }
    cout << res << endl;
    return 0;
}
