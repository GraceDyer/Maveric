int solve(int a[],int n,int L)
{
	int l,r,min ;
    int time=0 ;  
    for ( int i=0 ; i<n ; i++  ) 
    {
       l=a[i];
       r=L-a[i];
       if (l>=r)
           min=r;
       else 
           min=l;
       if ( time<= min)
           time=min;
       else
           time=time         ;                
    }
    return time;
    }
