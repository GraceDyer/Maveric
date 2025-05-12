int solve(int money[])
{
	int a=0,sum=0,flag=0;
    for(int i=1;i<=12;i++){
        a=a+300-money[i];
        if(a<0){
        	return -i;
        }
        sum=sum+a/100*100;
        a=a%100;
    }
    if(!flag){
        return sum*1.2+a;    
    }
}
