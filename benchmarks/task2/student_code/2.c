double getSalary(double hours)
{
    /********** Begin **********/
    if (hours <= 8)
        return 25 * hours;
    else if (hours <= 16)
        return 25 * 8 + 35 * (hours - 8);
    else 
        return 25 * 8 + 35 * 8 + 55 * (hours - 16);
    


    /**********  End  **********/
}

