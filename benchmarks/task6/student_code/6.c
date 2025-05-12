int solve(int n)
{
	int a,b,c;
    if(n<0){
        n=-1*n;
    }
    int flag=0;
    do {
        int j =n%10;
        if(j==3 || j==4){
            flag=1;
            break;
        }
        n=n/10;
    }
    while(n!=0);
    return flag;
}
