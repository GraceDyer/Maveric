double getSalary(double hours)
{
    /********** Begin **********/
    double money;
    if(hours<=8) 
    {
        money=25*hours;
    }
    else if(hours<=16)
    {
        money=25*8+35*(hours-8);
    }
    else if(hours>16)
    {
        money=25*8+35*8+55*(hours-16);
    }
    return money;
    /**********  End  **********/
}

