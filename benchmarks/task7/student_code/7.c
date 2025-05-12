int f(int x)
{
    int sum=0;
    for (int i=1;i<x;i++)
    {
        if (x%i==0)
        {
            sum+=i;
        }
    }
    return sum;
}
