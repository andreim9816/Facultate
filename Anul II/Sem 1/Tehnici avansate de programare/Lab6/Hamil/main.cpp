#include<vector>
#include<fstream>
#include<iostream>
#include<queue>

using namespace std;


int solutie = -1;
stare *bestStare = NULL;

struct stare
{
    int cost; // costul pana la nodul respectiv
    int level;
    int last_node; // ultimul nod (vecin)
    vector<bool> viz;
    vector<vector<int>>matrix; // matricea pt stare-ul respectiv
    stare*parinte;
};

void initstare(stare *eu, vector<bool>vec , int cost = 0, stare * parinte = NULL)
{
    eu->cost = cost;
    eu->last_node = 0;
    eu->parinte = parinte;
    eu->level = 1;
    eu->viz.resize(vec.size());

    int i;
    for(i = 0 ; i < vec.size() ; i++)
        eu->viz[i] = vec[i];
}

void printSol(stare *elem)
{
    if( elem == NULL)
        return ;
    printSol(elem->parinte);
    cout<<elem->last_node + 1 <<" ";
}

struct cmp
{
    bool operator()(const stare* a, const stare *b)
    {
        return a->cost > b->cost;
    }
};

int reducere(vector<vector<int>>&matrix)
{
    int reduc = 0;
    int dim = matrix.size();
    int i;

    for(i = 0 ; i < dim; i++)
    {
        int mini = -1;
            for(int j = 0 ; j < dim ; j++)
                if(matrix[i][j] != -1 && (matrix[i][j] < mini || mini == -1))
                    mini = matrix[i][j];

       if(mini > 0)
       {

        reduc += mini;

        for(int j = 0 ; j < dim ; j++)
            if(matrix[i][j] != -1 )
            matrix[i][j] = matrix[i][j] - mini;
       }
    }

    for( i = 0 ; i < dim; i++)
    {
        int mini = -1;
        for(int j = 0 ; j < dim ; j++)
            if(matrix[j][i] != -1 && (matrix[j][i] < mini || mini == -1))
             mini = matrix[j][i];

       if(mini > 0)
       {

       reduc += mini;

        for(int j = 0 ; j < dim ;j++)
            if(matrix[j][i] != -1)
             matrix[j][i] -= mini;
       }
    }
    return reduc;
}

int main()
{
    int n , j , reduc;
    ifstream fin("date.in");
    fin>>n;
    priority_queue<stare* , vector<stare*>, cmp>minHeap;
    vector<vector<int>>matrix;
    vector<bool>viz(n , false);
    viz[0] = true ;


    matrix.resize(n);
    int i;

    //citire
    for(i = 0 ; i < n ; i++)
    {
        matrix[i].resize(n);

        for(j = 0 ; j < n ; j++)
        {
            if( i == j )
                matrix[i][j] = -1;
            else fin>>matrix[i][j];
        }
    }

    reduc = reducere(matrix);
    // adauga starea initiala in heap
    stare* initial_stare = new stare;
    initstare(initial_stare , viz , 0 , NULL);

    initial_stare->matrix = matrix;
    initial_stare->cost = reduc;

    //introduc in heap
    minHeap.push(initial_stare);

    while(!minHeap.empty())
    {
        stare* stareCurr = minHeap.top();
        minHeap.pop();

        if(!(stareCurr->cost > solutie && solutie !=-1))
        {

            for(i = 1 ; i < n; i++)
            {
                if(stareCurr->viz[i] == false)
                {
                    stare* copil = new stare;
                    initstare(copil , stareCurr->viz , stareCurr->cost , stareCurr);

                    copil->level = stareCurr->level + 1;
                    copil->matrix = stareCurr->matrix;
                    copil->last_node = i;

                    // nod pe ultimul nivel
                    if(n - 1 == stareCurr->level)
                    {
                        copil->cost += copil->matrix[stareCurr->last_node][i] + copil->matrix[i][0];
                        if(copil->cost < solutie  || solutie == -1)
                        {
                            solutie = copil->cost;
                            bestStare = copil;
                        }
                    }
                    else
                    {
                        // pun -1 pe linie si coloana
                        for(j = 0 ; j < n ; j++)
                            copil->matrix[stareCurr->last_node][j] = -1;
                        for(j = 0 ; j < n ; j++)
                            copil->matrix[j][i] = - 1;

                        // coostul copilului e cat am redus inainte + latura asta + de la reducere
                        copil->matrix[i][0] = -1;
                        copil->cost += reducere(copil->matrix);
                        copil->cost += stareCurr->matrix[stareCurr->last_node][i];

                        if(copil->cost >= solutie && solutie != -1)
                            {
                                delete(copil);
                                continue;
                            }
                        copil->viz[i] = true;
                        minHeap.push(copil);
                    }
                }
            }
        }
        else delete(stareCurr);
    }

    cout<<"Costul minim este " << solutie <<endl;
    printSol(bestStare);
    cout<<" 1";

	return 0;
}