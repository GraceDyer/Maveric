//完成计算不包含x本身的因子和
int f(int x)
{
    int a=1,b=0;
    for(;a<x;a=a+1)
    {
        if(x%a==0)
            b=b+a;
    }
    return b;
}

