int solve(int a[])
{
    int store=0,xianyou=0;
    for (int i=1;i<=12;i++)
    {
        xianyou=xianyou+300-a[i];
        if (xianyou<0)
        {
            
            return -i;
        }
        else
        {
            int a=xianyou/100;
            xianyou%=100;
            store=store+a*100;
        }
    }
    double b=store*1.2+xianyou;
    return b;
}
