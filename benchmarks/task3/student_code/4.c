double vipShouFei(double money)
{
    double f=0;
    if (money <= 5000)
    {
        f = money * 0.01 * 0.85;
    }
    else
    {
        f=42.5;
    }
    return f;
}
