int f(int n,int m,int a[])
{
    int s = 0, num = 0;
	for (int i = 0; i < m; i++) 
	{
		s = s + a[i];
		if (s <= n) 
		{
			num = num + 1;
		}
		else 
		{
			s = s - a[i];
			num = num + 0;
		}
	}
    return num;
}