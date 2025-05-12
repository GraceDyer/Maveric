int solve(int a[])
{
	int cnt=0;int c=0;
    int flag=0;
    for(int i=1;i<=12;i++){
    	
        if(cnt+300<a[i]){
				return -i;
            }
        else{
            c+=(cnt+300-a[i])/100*100;
            cnt=(cnt+300-a[i])%100;
        }
                }
    return c*1.2+cnt;
    }
