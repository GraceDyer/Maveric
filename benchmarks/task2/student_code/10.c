double getSalary(double hours)
{
    /********** Begin **********/
    double salary;
    if (hours <= 8)
        salary = 25 * hours;
    else if (hours > 8 && hours <= 16)
        salary = 25 * 8 + (hours - 8) * 35;
    else
        salary = 25 * 8 + 35 * 8 + (hours - 16) * 55;
    return salary;



    /**********  End  **********/
}

