int f(int x)
{
    int b = 1;
    for (int i = 1; i < x; i++)
    {
        int t = 0;
        if (x % i == 0)
        {
            b+=i;
        }
    }
    return b;
}
