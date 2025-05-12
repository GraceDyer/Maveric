

int sum_fac(int n)
{
        /**********Program**********/
	int x,result=0;
        for(int i=1;i<n+1;i++)
        {
                x=1;
		for(int j=1;j<i+1;j++)
                {
                	
                        x=x*j;
                }
                result+=x;
        }



        /**********  End  **********/
        return result;
}
