int solve(int x)
{
	int yushu;
    x = abs(x);
    int jg = 0;

    while (x > 0)
    {
        yushu = x % 10;
        if (yushu == 3 || yushu == 4)
        {
            jg = 1;
            break;
        }
        x = (x - yushu) / 10;
    }
    if (x % 10 == 3 || x % 10 == 4)
    {
        jg = 1;
    }
	return jg;
}
