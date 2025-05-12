int f(int n,int m,int a[])
{
    int num=0,s=0;
    while ((n>0)&&(s<m))
    {
        if (n>=a[s])
        {
            n-=a[s];
            num+=1;
            s+=1;
        }
        else
        {
            s+=1;
        }
    }
    return s;
}