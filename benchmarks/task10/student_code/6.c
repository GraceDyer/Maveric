void sort (int date[],int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (date[i] > date [j])
			{
				int tmp = date[i];
				date[i] = date[j];
				date[j] = tmp;
			}
		}
	}
}

