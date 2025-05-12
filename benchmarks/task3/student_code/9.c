double vipShouFei(double m)
{
    double M;
    M = m * 0.01 * 0.85;
    if (M <= 42.5)
        return M;
    else
        return 42.5;
    
}
