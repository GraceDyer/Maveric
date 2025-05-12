double vipShouFei(double money)
{
    double x;
    x=money*0.01;
    if(x<=42.5)
    {
        x=money*0.01*0.85;
    }
    else
    {
        x=42.5;
    }
    return x;
}
