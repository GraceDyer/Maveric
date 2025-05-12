int f(int N,int M,int a[])
{
	int n=0;
	int num = 0;
	for (int i = 0; i < M; i++)
	{
		if (N >= a[i])
		{
			N = N - a[i];
			num++;
			//cout << " " << num << " ";
		}
        else
        {
            continue;

        
        }
	}
	return num;
}