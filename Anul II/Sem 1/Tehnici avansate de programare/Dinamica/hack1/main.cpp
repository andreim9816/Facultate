#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'maxValue' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY rounds
 */

long maxValue(int n, vector<vector<int>> rounds)
{
    int i;
    unsigned long long maxVal = 0;
    vector<int>investments( n , 0); // vector of investments

    for(i = 0 ; i < rounds.size() ; i++) // each contribution
    {
        int left, right , contrib;

        left = rounds[i][0];
        right = rounds[i][1];
        contrib = rounds[i][2];

        for(int j = left ; j <= right ; j++)
        {
            investments[j] += contrib;
            if(investments[j] > maxVal)
                maxVal = investments[j];
        }

    }

    return maxVal;
}

int main()
