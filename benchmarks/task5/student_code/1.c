int solve(int t[],int n,int len)
{
	int min;
	int time=0;//需要的时间初始化为0 
	for(int i=0;i<n;i++){
		min=t[i]<(len-t[i])?t[i]:(len-t[i]);
		if(time<min)
			time=min;//更新所需要的时间 
	}
	return time;
	}
