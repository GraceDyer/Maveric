int solve(int longe[],int n,int l)
{
	for(int i=0;i<n;i++)
	{
		if((l-longe[i])<longe[i])
			longe[i]=l-longe[i];
    }
    int time=longe[0];
    for(int i=1;i<n;i++)
    {
        if(longe[i]>time)
            time=longe[i];
    }
	return time;
}
