int f(int num)
{
    int yu, a;
    while (num >= 10)
    {
        a = 1;
        while (num != 0)
        {
            yu = num % 10;
            num /= 10;
            if (yu != 0)
            {
                a *= yu;
            }
        }
        num = a;
    }
    return num;
}