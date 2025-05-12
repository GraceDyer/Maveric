int f(int x)
{
    while (x >= 10)
    {
        int pro, n;
        pro = 1;
        while (x >= 10)
        {
            n = x % 10;
            x = x / 10;
            if (n != 0)
            {
                pro = pro * n;
            }
        }
        x = pro * x;
    }
    return x;
}