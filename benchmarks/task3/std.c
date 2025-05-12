
double std(double money)
{
    double ans = money*0.01*0.85;
    if (ans >= 42.5) ans = 42.5;
    return ans;
}
