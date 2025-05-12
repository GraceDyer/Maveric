int sum_fac(int n)
{
        /**********Program**********/
        int s=1,result=0;
        for (int i=1;i<=n;i++)
        {
                s=s*i;
                result+=s;
        }
        /**********  End  **********/
        return result;
}
