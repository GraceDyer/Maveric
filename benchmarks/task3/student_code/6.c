double vipShouFei(double money)
{
    if (money *  0.01 * 0.85 <= 42.5)
    {
        return money *  0.01 * 0.85;
    }
    else
    {
        return 42.5;
    }
    
}
