
int sum_fac(int n)
{
    /**********Program**********/
    int a = 1;
    int result = 0;
    for (int i = 1; i <= n; i++)
    {
        int a = 1;
        for (int j = 1; j <= i; j++)
        {
            a = a * j;
            //cout << a << "j" << j << endl;
        }

        
        //cout << i << " " << a << endl;
        result = result + a;
    }
        




    /**********  End  **********/
    return result;
}
