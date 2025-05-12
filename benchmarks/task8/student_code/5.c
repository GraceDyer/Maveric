int f(int n,int m,int arr[])
{
	int num=0;//num表示最多购买多少种，初始化为0 
	int i;
	for(i=0;i<m;i++)
    {
		if(n>=arr[i])//买得起
        { 
			n-=arr[i];//钱数减去猫粮的价格 
			num++; 
		}
	} 
    return num;
}