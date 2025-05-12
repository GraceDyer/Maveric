int solve(int a[])
{
    int n=12;
    int k=0;
    int u=0;
    for (int i=1;i<=12;i++)
    {
        k+=300-a[i];
        if (k<0)
        {
            return -i;
            break;
        }
        else
        {
            u+=k/100*100;
            k%=100;
        
        }
        if (i==12)
        {
            return k+u*1.2;
        }
    }

}
