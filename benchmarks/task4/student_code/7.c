
int sum_fac(int n)
{
        /**********Program**********/
        int result, s = 1;
        for (int i = 2; i <= n; i++)
        {       
                int m;
                m = i;
                s = 1;
                do
                {       
                        s = s*m;
                        m -= 1;
                }while(m != 1);
                result += s;
        }
        result += 1;

        /**********  End  **********/
        return result;
}
