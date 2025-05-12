int f(int n)
{
    int i=0;
    int k[100];
    int u=1;
    while(n>0)
    {
        k[i]=n%10;
        n=n/10;
        i+=1;
    }
    for(int j=0;j<i;j++)
    {
        if(k[j]!=0)
        {
            u=u*k[j];
        }
    }
    return u;
}