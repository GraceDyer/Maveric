int f(int x)
{
    int s = 1;
    while (x != 0)
    {
        if (x % 10 != 0)
        {
            s = s * (x % 10);
        }
        x = x / 10;
        if (x == 0)
        {
            x = s;
            if (x < 10)
                break;
            s = 1;
        }
    }
    return s;
}