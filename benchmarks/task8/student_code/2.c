int f(int N,int M,int a[])
{
    int s = 0;   
	for (int i = 1; i <= M; i++)
	{
		if (N >= a[i])
		{
			N = N - a[i];
			s++;
		}
		
	}
    return s;
}