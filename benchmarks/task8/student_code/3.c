int f(int money,int n,int a[])
{
    int num = 0;
    for (int i = 0; i < n; i++)
        {
            if (money >= a[i])
                {
                    num++;
                    money-=a[i];
                }
        }
    return num;
}