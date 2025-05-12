int f(int n,int m,int b[])
{
    int a = 0;
    for (int i = 0; i < m; i++)
    {
        if (n >= b[i])
        {
            a++;
            n = n - b[i];
        }
    }
    return a;
}