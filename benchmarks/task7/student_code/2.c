int f(int x)
{
    int y = 0;
    for (int i = 1; i < x; i++)
    {
        if (x % i == 0)
        {
            y = y + i;
        }
    }
    return y;
}
