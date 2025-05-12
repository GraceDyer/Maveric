
int f(int x)
{
    int yu, sheng, jie = 1;
    while (x != 0)
    {
        yu = x % 10;
        sheng = x / 10;
        if (yu != 0)
            jie *= yu;
        x = sheng;
    }
    return jie;
}