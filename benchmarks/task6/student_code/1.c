int solve(int x)
{
	int c,a0;
    int a = 1;
    while (a > 0)
    {
        a0 = x % 10;
        if (a0 == 3 || a0 == 4)
        {
            c = 1;
            break;
        }
        x = x / 10;
        if (x == 3 || x == 4)
        {
            c = 1;
            
            break;
        }
        if (x < 10)
            break;
    }
    return c;
}
