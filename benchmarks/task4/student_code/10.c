int sum_fac(int n)
{
        /**********Program**********/
       int ssum=0;
for (int i=n;i>=1;i--)
{
       int sum=1;
        for (int q=i;q>=1;q--)
        {
              sum=sum*q  ;
        }
        ssum=ssum+sum;


}


        /**********  End  **********/
        return ssum;
}
