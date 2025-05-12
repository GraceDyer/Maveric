int solve(int a[])
{
    int now = 0, save = 0;
    for (int i = 1;i <= 12;i++){
        now += 300 - a[i];
        if (now < 0) return -i;
        else {
            save += now / 100 * 100;
            now %= 100;
        }
    }
    int ans = (1.2*save + now + 0.5);
    return ans;
}
