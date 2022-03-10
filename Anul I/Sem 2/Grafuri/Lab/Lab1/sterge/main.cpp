#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("date");
void citire(istream &in)
{

    char s[200];
    in.getline(s,200);
    cout<<s;
}

int main()
{
    citire(fin);
    return 0;
}
