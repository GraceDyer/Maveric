int f(int n,int m,int arr[])
{
	int num=0;//num表示最多购买多少种，初始化为0 
	int i;
	for(i=0;i<m;i++)
    {
		if(n>=arr[i])
        {
			n=n-arr[i];//钱数减去猫粮的价格 
			num=num+1; 
		}
        else 
        {
            continue;
        }
	} 
    return num;
}