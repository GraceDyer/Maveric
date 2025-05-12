

int std(int pos[],int n,int len)
{
    int ltime = -1;
    for (int i = 0; i < n; i++)
    {
        int time = (pos[i] <= len / 2 ? pos[i] : len - pos[i]);
        if (time > ltime)
            ltime = time;
    }
    return ltime;
}
