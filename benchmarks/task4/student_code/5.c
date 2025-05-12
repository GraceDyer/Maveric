
int sum_fac(int n)
{
        /**********Program**********/
        int result;
        for (int i = 1;i <= n;i++)
        {
                int product = 1;
                for (int k = 1;k<=i;k++)
                        product*=k;
                result+=product;
        }
        /**********  End  **********/
        return result;
}
