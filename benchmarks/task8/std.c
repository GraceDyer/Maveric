int std(int n,int m,int a[]){
    int ans = 0;
    for (int i = 0;i < m;i++){
        if (n >= a[i]) ans++, n -= a[i];
    }
    return ans;
}
