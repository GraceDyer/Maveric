int solve(int n)
{
	int c;
    while (n%10!=0)
    {
        int x=n%10;
        if (x==3 ||x==4)
        {
            c+=1;
        }
        n=n/10;
    }
    return c;
    }
