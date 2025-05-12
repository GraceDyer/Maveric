int solve(int n)
{
	int n;
    while(n!=0)
    {
        int k=n%10;
        if(k==3 || k==4)
        {
            return 1;
        }
        n=(n-k)/10;
    }
    return 0;
    }
