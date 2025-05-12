void sort(int data[], int len)
{
    for(int i=1;i<len;i++)
    {
        for(int j=0;j<i;j++)
        {
            if (data[j]>data[i])
            {
                int shit=data[i];
                data[i]=data[j];
                data[j]=shit;
            }
        } 
    }
}
