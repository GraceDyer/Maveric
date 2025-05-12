int f(int n,int m,int a[])
{
    int s;
    for (int x = 0; x < m; x ++)
    {
        if (n >= a[x])
        {
            s = s + 1;
            n = n - a[x];
            
        }
        else
            continue;
    }
    return s;
}