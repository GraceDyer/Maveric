int solve(int n[])
{
int  m = 0, c= 0;
    for(int x = 1; x <= 12; x++)
    {
        m=m+300-n[x];
        c=c+m/100;
        m=m%100;
        if (m < 0)
        {
        	return -x;
        }
    }
        return m + c*100*1.2;
        }
