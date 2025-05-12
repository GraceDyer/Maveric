double getSalary(double hours)
{
    /********** Begin **********/
    double s;
    if (hours <= 8)
    {
        s = 25 * hours;
    }
    else if (hours > 8 && hours <= 16)
    {
        s = 25 * 8 + 35 * (hours - 8);
    } 
    else
    {
        s = 25 * 8 + 35 * 8 + 55 * (hours - 16);
    }

    /**********  End  **********/
}
