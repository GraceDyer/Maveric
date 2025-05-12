void sort(int data[],int len)
{
	int jicun3,jicun4;
    for(int m=0; m<len; m++)
    {
        for(int q=m; q<len; q++)
        {
            if(data[m]>data[q])
            {
                jicun3=data[m];
                data[m]=data[q];
                data[q]=jicun3;
            }
        }
    }
}
