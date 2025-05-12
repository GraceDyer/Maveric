
int std(int n)
{
    while (n >= 10){
        int tmp = n,p = 1;
        while(tmp){
            int t = tmp % 10;
            if (t) p *= t;
            tmp /= 10;
        }
        n = p;
    }
    return n;
}
