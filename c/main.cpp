#include <bits/stdc++.h>

using namespace std;

int seg[10000];
int n,m,was[30002];
vector<pair<int, int> > por;
vector<int> a, b;

int get_sum(int l,int r) {
    if(l>r){
        return 0;
    }
    if(l%2){
        return seg[l]+get_sum(l+1,r);
    }
    if(r%2==0) {
        return seg[r]+get_sum(l,r-1);
    }
    return get_sum(l/2,r/2);
}

int main() {
    cin >> n >> m;
    a.resize(m);
    b.resize(n);
    for (int i=0;i<m;i++){
        cin >> a[i];
    }
    for (int i=0;i<m;i++){
        cin >> b[i];
    }
    int pos=0;

    for (int i=0;i<m;i++){
        if (was[a[i]]==0){
            while (b[pos]!=a[i]){
                was[b[pos]] = 1;
                por.push_back(make_pair(b[pos], 0));
                pos++;
            }
            was[b[pos]]=1;
            pos++;
        }
        por.push_back(make_pair(a[i], 1));
    }
    cout << size(por) << endl;
    for (int i=0;i<m;i++){
        was[i+1]=size(por);
    }
    for (int i=size(por);i>0;i--){
        int gg=por[i].first;
        if (was[gg]==size(por)) {
            por[i].first=n;
        } else {
            por[i].first=get_sum(30000,30000+was[gg]);
            int pos=30000+was[gg];
            while (pos>0){
                seg[pos]--;
                pos/=2;
            }
        }
        was[gg]=i;
        int pos=30000+was[gg];
        while (pos>0){
            seg[pos]++;
            pos/=2;
        }
    }
    for (int i=0;i<size(por);i++) {
        cout << por[i].first << " ";
    }
    return 0;
}