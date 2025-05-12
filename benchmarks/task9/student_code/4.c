int f(int n)
{
    long c;
    int m=1;
    int d;
    while(1){
        c=n;
        m=1;
        while(c>0){
            d=c%10;
            c=c/10;
            if(d!=0){
                m*=d;
            }
        }
        n=m;
        if(n<10){
            break;
        }
    }
    return n;
}