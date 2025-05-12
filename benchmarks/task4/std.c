
int std(int n)
{
	int ans = 0,p = 1;
	for (int i = 1;i <= n;i++)
	{
		p *= i;
		ans += p;
	}
	return ans;
}
