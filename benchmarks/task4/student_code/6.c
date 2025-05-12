int sum_fac(int n)
{
        /**********Program**********/
        int i,m;
        int s=1;
        int r = 0;
        for (i=1; i<=n; i++)
        {
                int s=1;
                for (m=1; m<=i; m++)
                        s*=m;
                        r+=s;         
        }

        /**********  End  **********/
        return r;
}
