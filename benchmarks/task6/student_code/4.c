int solve(int n)
{
	int a;
    int i=1;
    int m=0;
    if(n<0){
        n=-n;
    }
    while(n!=0){
        a=n%10;
        n=n/10;
        if (a==3||a==4){
            m=1;
            break;
        }
    }
	return m;
    }
