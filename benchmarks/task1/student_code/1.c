int solve(int a[])
{
    int s=0;
    int x=0;
    for (int i=1;i<=12;i++)
    {
        x=x+300-a[i];
        if (x<0)
        {
            return -i;
        }
        else
        {
            int a=x/100;
            x=x%100;
            s=s+a*100;
        }
    }
    double b=s*1.2+x;
    return b;
}
