int solve(int a[],int n,int L)
{
	int q;
    int c;
    if (a[0]<L-a[0]){
        c=a[0];
    }
    else{
        c=L-a[0];
    }
    int y;
    for(int i=1;i<n;i++){
        if (a[i]<L-a[i]){
            y=a[i];
        }
        else{
            y=L-a[i];
        }
        if (y>c){
            c=y;
        }
    }
    return c;
    }
