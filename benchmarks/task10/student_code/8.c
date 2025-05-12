void sort(int data[], int len) 
{
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++) 
		{
			if (data[i] > data[j])
			{
				int x = data[i];
				data[i] = data[j];
				data[j] = x;
			}
		}
	}
}
