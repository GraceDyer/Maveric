
int solve(int pos[10000], int n,int len)
{
    
    int mins = 0;
    int tm = 0;
    for (int i = 0; i < n; i++) {
        
        if (2 * pos[i] <= len) {
            tm = pos[i];
        }
        else if (2 * pos[i] > len) {
            tm = len - pos[i];
        }
        if (mins <= tm) {
            mins = tm;
        }

    }
    return mins;
}
