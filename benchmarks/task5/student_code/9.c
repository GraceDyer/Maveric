int solve(int a[],int n,int L)
{   
    int t=0;
    int sh=0;
    for (int i=0; i<n; i++)
    {
        if (a[i]*2<L)
        {
            t=a[i];
        }
        else
        {
            t=L-a[i];
        }
        
        if (sh<t)
        {
            sh=t;
        }

    }
    return sh;
}
