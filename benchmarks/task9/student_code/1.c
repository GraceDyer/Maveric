int f(int x)    
{
    int n,num =1;
    while (x > 10)
    {
        n = x % 10;
        x = x / 10;
        if (n != 0)
        {
            num *= n;
        }   
    }
    return num * x;
}  