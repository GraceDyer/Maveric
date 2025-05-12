double getSalary(double hours)
{
    /********** Begin **********/
    double m;
    if (hours <= 8)
        m = 25 * hours;
    if (hours > 8 && hours <= 16)
        m = 25 * 8 + (hours - 8) * 35;
    if (hours >= 16)
        m = 25 * 8 + 8 * 35 +(hours - 16) * 55;
    return m;
    /**********  End  **********/
}
