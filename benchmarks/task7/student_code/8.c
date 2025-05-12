int f(int x)
{
    int h=0;
    for (int i=1 ; i < x; i++)
    {
        if (x % i == 0)
        {
            h=h+i;
        }
    }
    return h;
}

