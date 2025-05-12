
int sum_fac(int n)
{
        /**********Program**********/
        int result;
        for (int i = 1;i <= n;i++)
        {
                int p = 1;
                for (int k = 1;k<=i;k++)
                        p*=k;
                result+=p;
        }



        /**********  End  **********/
        return result;
}

