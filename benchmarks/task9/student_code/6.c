int f(int x)
{
    while (x > 9)
    {
        int ji = 1;
        while (x > 0)
        {
            int s;
            s = x % 10;
            x = x / 10;
            if (s > 0)
            {
                ji = ji * s;
            }
        }
        x = ji;
    }
    return x;
}