int solve(int a[],int n,int L){
    int r, l, real, t;
    int T = 0;
    for (int i = 0; i < n; i++)
    {
        l = a[i];
        r = L - l;
        if (r > l){
            real = l;
        }
        else
            real = r;
        t = real / 1;
        if (t > T){
            T = t;
        }
    }
    return T;
}

