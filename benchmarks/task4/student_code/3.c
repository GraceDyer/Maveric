int sum_fac(int n)
{
        /**********Program**********/
        int m = 0;
        for (int i = 1; i <=n; i++)
        {
                int c = 1;
                for(int a = 1; a <=i; a++)
                {
                        c = c * a;
                }
                m = m + c;
        }
        int result;
        result = m;



        /**********  End  **********/
        return result;
}
