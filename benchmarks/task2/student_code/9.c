double getSalary(double hours)
{
    double s,a;
    /********** Begin **********/
    if (hours<=8)
        a = hours*25;
    else if (hours>8 && hours<=16)
        a = (hours-8)*35+25*8;
    else
        a = (hours-16)*55+25*8+35*8;


    /**********  End  **********/
}

