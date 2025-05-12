/**********Program**********/
double vipShouFei(double money)
{
    double fee;
    fee=money*0.01*0.85;
    if (fee>=42.5)
    {
        return 42.5;
    }
    else
    {
        return fee;
    }
}
