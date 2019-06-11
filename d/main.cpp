#include <iostream>

using namespace std;


int best[300002];
int dp[300002][64];
int pref[300002][64];
int c[63][63];
int cnt[63][64];
int cnt_bits[63];

int main() {
    long long n,m,k,add;
    cin >> n >> m >> k;
    for (int i=0;i<=62;i++) {
        c[i][0]=1;
        for (int j=1;j<=i;j++) {
            c[i][j]=c[i-1][j-1]+c[i-1][j];
            if (c[i][j]>=(1e9+7)) {
                c[i][j]-=(1e9+7);
            }
        }
    }
    for (int i=0;i<=62;i++) {
        cnt[i][1]=1;
        for (int j=2;j<=i+1;j++) {
            cnt[i][j]=(1LL*cnt[i-1][j-1]*(j-1))%(long long)(1e9+7);
            cnt[i][j]+=(1LL*cnt[i-1][j]*j)%(long long)(1e9+7);
            if (cnt[i][j]>=1e9+7){
                cnt[i][j]-=1e9+7;
            }
        }
    }
    for (int b=62-1;b>=0;b--)
        if ((k >> b)&1) {
            for (int i=0;i<=b;i++) {
                cnt_bits[add+i]+=c[b][i];
                if (cnt_bits[add+i]>=(1e9+7)){
                    cnt_bits[add+ i]-=(1e9+7);
                }
            }
            add++;
        }
    cnt_bits[add]++;
    if (cnt_bits[add]>=(1e9+7)){
        cnt_bits[add]-=(1e9+7);
    }
    fill(best,best+n,-(1e9+1));
    for (int i=0;i<m;i++) {
        int l,r;
        cin >> l >> r;
        l--;
        r--;
        best[r]=max(best[r],l);
    }
    for (int i=1; i<n;i++) {
        best[i]=max(best[i],best[i - 1]);
    }
    for (int i = 0; i < n; i++) {
        dp[i][1]=(best[i]==(-1e9+1)?1:0);
        for (int j=2;j<=min(i+1,63);j++){
            if (best[i]==-(1e9+1)) {
                dp[i][j]=pref[i-1][j-1];
            }
            else {
                dp[i][j]=pref[i-1][j-1]-(best[i]>0?pref[best[i]-1][j-1]:0);
                if (dp[i][j]<0)
                    dp[i][j]+=(1e9+7);
            }
        }
        if (i==0) {
            for (int j=1;j<=62+1;j++)
                pref[i][j]=dp[i][j];
        }
        else {
            for (int j=1;j<=62+1;j++) {
                pref[i][j]=pref[i-1][j] + dp[i][j];
                if (pref[i][j] >= (1e9+7))
                    pref[i][j] -= (1e9+7);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= 62; i++)
        for (int j = 1; j <= min(n, i + 1); j++)
        {
            ans += 1LL * dp[n - 1][j] * cnt[i][j] % (1e9+7) * cnt_bits[i] % (1e9+7);
            if (ans >= (1e9+7))
                ans -= (1e9+7);
        }
    cout << ans << endl;
    return 0;
}