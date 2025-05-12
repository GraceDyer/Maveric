void sort(int data[], int len)
{
	for (int i = 1; i <= len; i++)
	{
		for (int j = 1; j <= len - i; j++)
		{
			//cout << "data[i]:" << data[i] << " data[j]:" << j << endl;
			if (data[j + 1] < data[j])
			{
				//cout << "aaaaaaaaa" << endl;
				int a = data[j + 1];
				data[j + 1] = data[j];
				data[j] = a;
			}
		}
	}
}
