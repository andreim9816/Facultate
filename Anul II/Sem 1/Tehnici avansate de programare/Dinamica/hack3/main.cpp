#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'maximumClusterQuality' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY speed
 *  2. INTEGER_ARRAY reliability
 *  3. INTEGER maxMachines
 */


struct cmp_pq
{
   bool operator()(pair<int,int>x, pair<int,int> y)
    {
     if(x.first < y.first) /// sorted desc by the speed value
        return true;
       return false;
    }
};

int returnMax(priority_queue< pair<int,int>, vector<pair<int,int>>, cmp_pq >pq ,vector<pair<int,int>>v,int n, int i, int xMachines)
{
    int elem = v[i].second; // reliabilty value - the minimum one -
    int S = v[i].first; // sum of speeds
    int k = 1;

        while(pq.size() > 0 && k < xMachines) // while we didnt reach the maximumValue
        {
            pair<int,int> x = pq.top();

            pq.pop();

            // if it's not the same pair and we can choose it so elem is the minimum, we add it to the sum
            if(x.second > elem || (x.second == elem && x.first != v[i].first))
            {
                k++;
                S+= x.first;
            }
        }

    return S * elem; // returns the result
}

long maximumClusterQuality(vector<int> speed, vector<int> reliability, int maxMachines)
{
    int i=0, maxValue  = -1;

    int n = speed.size(); // number of elements

    // vector of pairs of elements
     vector<pair<int,int>>v;

    //priority queue, sortez desc by the speed
    priority_queue< pair<int,int>, vector<pair<int,int>>, cmp_pq >pq;

    // construct priority_queue and vector
    for(i = 0 ; i < n ; i++)
     {
         pq.push( {speed[i], reliability[i]} );
         v.push_back({speed[i],reliability[i]});
     }

    // for each reliability value, we consider it the minimum one. Then, we find other options (but maximum maxMachines) so we maximize the product

    for(i = 0 ; i < n ; i++)
    {
        int value = returnMax(pq, v, n , i, maxMachines);
        if(value > maxValue)
            maxValue = value;
    }
    return maxValue;
}
