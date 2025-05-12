int f(int n,int m,int x[])
{
    int cnt = 0;
    for (int i=0;i<m;i++)
    {
        if (n>=x[i])
        {
        n=n-x[i];
        cnt++;
        }
    }
    return cnt;
}