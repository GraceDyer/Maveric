
int solve(int a[], int n, int L)
{
    int k = 0;
    int t = 0;
    int i = 0;
    while (i <= n - 1)
    {
        if (a[i] == L / 2)
            t = L / 2;
        if (a[i] > L / 2)
            k = L - a[i];
        if (a[i] < L / 2)
            k = a[i];
        if (t <= k)
            t = k;
        i++;
    }
    return t;
}
