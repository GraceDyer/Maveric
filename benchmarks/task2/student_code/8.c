#include <stdio.h>
double getSalary(double ho)
{
    /********** Begin **********/
    int m=0;
    if (ho<=8)
    {
        m=m+ho*25;
    }
    else if (ho>8&&ho<=16)
    {
        m=8*25+35*(ho-8);
    }
    else
        m=8*25+8*35+(ho-16)*55;
    return m;
    /**********  End  **********/
}
