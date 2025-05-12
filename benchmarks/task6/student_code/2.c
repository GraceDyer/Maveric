int solve(int n)
{
	if (n < 0)
        n *= -1;
    int i = 0;
    int a, b = n;
    while (b != 0)
    {
        a = b % 10;
        b = b / 10;
        if (a == 3 || a == 4)
        {
            i = 1;
            break;
        }
    }
	return i;
}
