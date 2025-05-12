int solve(int x)
{
	if (x < 0)
        x = -x;
    while (x != 0)
    {
        int a = x % 10;
        if (a == 3 || a == 4)
        {
        	return 1;
        }
            
        x = x / 10;
        if (x == 0)
        {
			return 0;
        }
            
    }
}
