int f(int x)
{
    do
    {
        int b;
        int pro = 1;
        while (x > 10)
        {
            b = x % 10;
            x = x / 10;
            if (b != 0)
            {
                pro = pro * b;
            }
        }
        x = pro * x;
    }while (x > 10);
    return x;
}