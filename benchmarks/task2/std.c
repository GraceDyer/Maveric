

double std(double hours)
{
    /********** Begin **********/
    double ans = 0;
    if (hours <= 8) ans = hours*25;
    else if (hours <= 16) ans = 200 + (hours - 8)*35;
    else ans = 200 + 280 + (hours - 16)*55;
    return ans;
    /**********  End  **********/
}
