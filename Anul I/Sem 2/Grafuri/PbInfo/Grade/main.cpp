#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n,q;
    cin>>n>>q;
    int a[n][301];
    int i,j,k;
    for(i=0;i<n;i++)
    {
        cin>>a[i][0];
        for(j=1;j<=a[i][0];j++)
            cin>>a[i][j];
    }

    for(i=0;i<q;i++)
    {
        int x,y;
        cin>>x>>y;
        cout<<a[x][y+1]<<"\n";
    }

    return 0;
}
