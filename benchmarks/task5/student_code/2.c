int solve(int a[],int n,int gan)
{
	int m;
    for (int i=0;i<n;i++){
        if(a[i]>gan/2){
            a[i]=gan-a[i];
        }
        if(a[i]>m){
            m=a[i];
        }
    }
    return m;
    }
