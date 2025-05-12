int std(int a[])
{
    int save = 0,rem = 0;
    for (int i = 1;i <= 12;i++){
        rem += 300 - a[i];
        if (rem < 0) return -i;
        save += rem / 100 * 100;
        rem %= 100;
    }
    int ans = (double)save*1.2 + rem;
    return ans;
}