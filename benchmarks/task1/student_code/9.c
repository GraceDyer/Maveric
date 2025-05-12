int solve(int n[])
{
	int x=0,m=0,c=0;		// 
	for(int x=1;x<=12;x++)	// 十二个月 
	{				// 输入每个月预算 
		m=m+300-n[x];			// 余钱 
		c=c+m/100;			// 存入c个整百到妈妈手上 
		m=m%100;			// 存入后剩下得钱  
		if(m<0)				// 钱不够 小于0 
		{
			return -x;		//输出当前-月份 结束程序 
			return 0;			
		}
	}
	return m+100*c*1.2;
	}
