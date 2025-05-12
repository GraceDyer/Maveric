
int sum_fac(int n)
{
        /**********Program**********/
        int result=0;
        int a=1;
        for(int i=1;i<=n;i++)
        {
                for(int j=1;j<=i;j++)
                        a=a*j;
                result+=a;
                a=1;
        }
        /**********  End  **********/
        return result;
}
