double getSalary(double hours)
{
    /********** Begin **********/
    int m = 0;
    if (hours <= 8)
        m = hours * 25;
    else if (hours > 8 && hours <= 16)
        m = 8 * 25 + (hours - 8) * 35;
    else
        m = 8 * 25 + 8 * 35 + (hours -16) * 55;
    return m;

    /**********  End  **********/
}
