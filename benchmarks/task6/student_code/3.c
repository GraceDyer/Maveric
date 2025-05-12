int solve(int x)
{
	int flag = 0;
	while (x != 0)
	{
		int  p = x % 10;
		if (p == 3 || p==4)
		{
			flag = 1;
			break;
		}
		x = x / 10;
	}
	return flag;
    }
