
int std(int n){
    if (n < 0) n = -n;
    int ans = 0;
    while (n){
        int t = n % 10;
        if (t == 3 || t == 4) ans = 1;
        n /= 10;
    }
    return ans;
}