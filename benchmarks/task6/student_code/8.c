int solve(int x)
{
	int n = 0;
    if (x < 0)
    {
        x = -x;
    }

    while (x != 0)
    {
        if (x % 10 == 3 || x % 10 ==4)
        {
            n = 1;
            break;
        }
        x = x / 10;
    }
	return n;
}
