#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

int intervMin = -1, intervMax = 2;
int popSize = 20;
int crSize = 22;
int etape = 50;
double precizion = 6;
double probCrossover = 0.25;
double probMutation = 0.1;

double fitnesss(double x)
{
    //-x^3 + x + 2
	return -(x * x) + x + 2;
}

struct Cromozom
{
    double value, fit, prob;
    bool data[1000];
};

void initCromozom(Cromozom &c)
{
    int i;
    for( i = 0 ; i < crSize ; i++)
        c.data[i] = rand() %2;
    c.value = c.fit = c.prob = 0.0;
}

void calcValueAndFit(Cromozom& c)
{
    int i;
    c.value = 0;
    for(i = 0 ; i < crSize ; i++)
        if(c.data[i] == true)
    c.value += pow(2, crSize - i -1);

   double numarator = intervMax - intervMin;
   double numitor = pow(2, crSize) - 1;
   double coef = (double)numarator / numitor;

   c.value = (double)c.value * coef + intervMin;
   c.fit = fitnesss(c.value);
}

void calcProb(Cromozom &c, double suma)
{
    c.prob = (double)c.fit / suma;
}

void printCromozom(Cromozom c)
{
    int i;
    for(i = 0 ; i < crSize ; i++)
        cout<<c.data[i];
    cout<<" ";
}

void printCromozomes(vector<Cromozom>&cromozomes)
{
	for(int i = 0 ; i < popSize ; i++)
	{
		cout<<i+1 << " ";
		//print binary value
        printCromozom(cromozomes[i]);
			//printf("%d", b);

		//print actual value
		//printf(" x=%.6Lf", cromozomes[i].value);
		cout<<"x= " <<cromozomes[i].value<<"   ";
		//print fitness
		cout<<"f= " << cromozomes[i].fit<<endl;
		//printf(" f= %.10Lf\n", cromozomes[i].fitness);
	}
}

double findMax(vector<Cromozom> cromozomes)
{
	double maxi = cromozomes[0].fit;
    //cout<<"\n\n---------------\n\n";
	for (int i = 1; i < popSize; i++)
	{   //cout<<cromozomes[i].fit<<endl;
		if (cromozomes[i].fit > maxi)
			maxi = cromozomes[i].fit;
	}
	//cout<<"\n\n---------------\n\n";
	return maxi;
}

double findAvg(vector<Cromozom> cromozomes)
{
	double sum =0;

	for (int i = 0; i < popSize; i++)
     sum += cromozomes[i].fit;


	return (double) sum/popSize;
}

int cromozomiDiferiti ( Cromozom x , Cromozom y)
{
    int i;
    for( i = 0 ; i < crSize ; i++)
        if(x.data[i] == y.data[i])
        return 0;
    return 1;
}

vector<Cromozom> urmGeneratie(vector<Cromozom>&Cr)
{
    double totalFit = 0 ;
    int i,j;

    default_random_engine generator;
    generator.seed(time(NULL));

    uniform_real_distribution<double>distribution(0.0 , 1.0);


    // initializeaza
    for(i = 0 ; i < popSize ; i++)
    {
        totalFit += Cr[i].fit;
    }

    // calculeaza probabilitatea
    for(i = 0 ; i < popSize ; i++)
        calcProb(Cr[i] , totalFit);

    vector<double>intervale;
    intervale.clear();

    intervale.push_back((Cr[0].prob));
    for(i = 1 ; i < popSize ; i++)
    {
        double val = Cr[i].prob + intervale[i-1];
        intervale.push_back(val);
    }

    vector<Cromozom>urmGen;
    urmGen.clear();

    for(i = 0 ; i < popSize ; i++)
    {
        double u = distribution(generator);
        // cautare binara indice
        int st = 0;
        int dr = popSize -1;
        int m;
        int poz = -1;
        poz = lower_bound(intervale.begin(), intervale.end() , u) - intervale.begin();
       // if(u >= intervale[0] && u <= intervale[1])
       //     poz = 1;
        while(st<=dr)
        {
            if(dr == 0)
            {
                poz = 0;
                break;
            }

            m = (st + dr) /2;
            if( intervale[m] <= u && u <= intervale[m+1])
                {
                    poz = m+1;
                    break;
                }
            else if(u < intervale[m])
                dr = m - 1;
            else st = m + 1;
        }

        urmGen.push_back(Cr[poz]);
    }

    // incrucisare
    vector<bool>participa;
    participa.resize(popSize , false);

   // cout<<"Probabilitatea de incrucisare este " << probCrossover<<endl;
    for(i = 0 ; i < popSize ; i++)
    {
        double u = distribution(generator);

     //   cout<< "\n"<< i + 1 <<". ";printCromozom(Cr[i]);
     //   cout<<" u= " << u;

        if(u < probCrossover) // face parte
        {
            participa[i] = true;
    //        cout<<" < " << probCrossover<< " participa";
        }
    }

    // are loc incrucisarea
    for(i = 0 ; i < popSize -1 ; i++)
     if(participa[i] == true)
      for(j = i + 1 ; j < popSize ; j++)
            if(participa[j] == true && cromozomiDiferiti(urmGen[i],urmGen[j]))
        {
            int pozRupere = rand() % (crSize-1);
          //  cout<<"\n Recombinare dintre cromozomul " << i+1 <<"  si " << j+1<<" punct "<<pozRupere <<" \n";

            for(int poz = 0 ; poz <= pozRupere ; poz++)
            {
                bool aux;
                aux = Cr[i].data[poz];
                Cr[i].data[poz] = Cr[j].data[poz];
                Cr[j].data[poz] = aux;
            }

            participa[i] = participa[j] = false;
            calcValueAndFit(urmGen[i]);
            calcValueAndFit(urmGen[j]);

         //   cout<<"Rezultat: ";
         //   printCromozom(urmGen[i]); cout<<" ";
        //    printCromozom(urmGen[j]);

            break; // sa nu mai faca cromozomul i si cu altul

        }

    //    cout<<"\nDupa recombinare:\n ";
    //    printCromozomes(urmGen);

        // MUTATIE
      //  cout<<"\nProbabilitatea de mutatie este " << probMutation<<endl;

      //  cout <<"\S-au mutat cromozomii:\n";
        for(i = 0 ; i < popSize ; i++)
        {
            bool mutat = false;
            for(j = 0 ; j < crSize ; j++)
            {
                double u = distribution(generator);

                if(u < probMutation)
                {
                    mutat = true;
                    urmGen[i].data[j] = !urmGen[i].data[j];
                }
            }

            if(mutat == true)
            {
          //      cout<<i<<" ";
                calcValueAndFit(urmGen[i]);
            }
        }

    return urmGen;
}

int main()
{
    double totalFit = 0 ;
    int i,j;

    default_random_engine generator;
    generator.seed(time(NULL));

    uniform_real_distribution<double>distribution(0.0 , 1.0);
    srand(time(NULL));

    ifstream fin("date.in");
    fin>>popSize >> intervMin >> intervMax >> precizion >> probCrossover >> probMutation >> etape;
    crSize = log2( (intervMax - intervMin) * pow(10 , precizion)) + 1;

    vector<Cromozom>Cr;
    Cr.resize(popSize);

    // initializeaza
    for(i = 0 ; i < popSize ; i++)
    {
        initCromozom(Cr[i]);
        calcValueAndFit(Cr[i]);
        totalFit += Cr[i].fit;
    }

    // calculeaza probabilitatea
    for(i = 0 ; i < popSize ; i++)
        calcProb(Cr[i] , totalFit);

    // prima afisare
    cout<<"Populatia initiala \n";
    printCromozomes(Cr);
    cout<<endl<<endl;

    // probabilitiati de selectie
    cout<<"Probabilitati de selectie\n";
    for(i = 0 ; i < popSize ; i++)
        cout<<i+1 <<". " << Cr[i].prob<<endl;

    // genereaza intervalele
    cout<<"\nIntervalele prob de selectie sunt \n0 ";
    vector<double>intervale;
    intervale.push_back((Cr[0].prob));
    for(i = 1 ; i < popSize ; i++)
    {
        double val = Cr[i].prob + intervale[i-1];
        intervale.push_back(val);
        cout<<intervale[i]<<" ";
    }


    // incepe cu generarea urmaotarelor generatii
    vector<Cromozom>urmGen;

    /// SELECTIA
    cout<<endl<<endl;
    for(i = 0 ; i < popSize ; i++)
    {
        double u = distribution(generator);
        cout<<"u = " << u<< "   ";
        // cautare binara indice
        int st = 0;
        int dr = popSize -1;
        int m;
        int poz;

        while(st<=dr)
        {
            m = (st + dr) /2;
            if( intervale[m] <= u && u <= intervale[m+1])
                {
                    poz = m + 1;
                    break;
                }
            else if(u < intervale[m])
                dr = m - 1;
            else st = m + 1;
        }

        urmGen.push_back(Cr[poz]);
        cout<<"Selectam cromozomul " << poz<<"\n";
    }

    // ce am obtinut dupa selectie
    cout<<"\nDupa selectie:\n";
    printCromozomes(urmGen);

    // incrucisare
    vector<bool>participa;
    participa.resize(popSize , false);

    cout<<"Probabilitatea de incrucisare este " << probCrossover<<endl;
    for(i = 0 ; i < popSize ; i++)
    {
        double u = distribution(generator);

        cout<< "\n"<< i + 1 <<". ";printCromozom(Cr[i]);
        cout<<" u= " << u;

        if(u < probCrossover) // face parte
        {
            participa[i] = true;
            cout<<" < " << probCrossover<< " participa";
        }
    }

    // are loc incrucisarea
    for(i = 0 ; i < popSize -1 ; i++)
     if(participa[i] == true)
      for(j = i + 1 ; j < popSize ; j++)
            if(participa[j] == true && cromozomiDiferiti(urmGen[i],urmGen[j]))
        {
            int pozRupere = rand() % (crSize-1);
            cout<<"\n Recombinare dintre cromozomul " << i+1 <<"  si " << j+1<<" punct "<<pozRupere <<" \n";

            for(int poz = 0 ; poz <= pozRupere ; poz++)
            {
                bool aux;
                aux = Cr[i].data[poz];
                Cr[i].data[poz] = Cr[j].data[poz];
                Cr[j].data[poz] = aux;
            }

            participa[i] = participa[j] = false;
            calcValueAndFit(urmGen[i]);
            calcValueAndFit(urmGen[j]);

            cout<<"Rezultat: ";
            printCromozom(urmGen[i]); cout<<" ";
            printCromozom(urmGen[j]);

            break; // sa nu mai faca cromozomul i si cu altul

        }

        cout<<"\nDupa recombinare:\n ";
        printCromozomes(urmGen);

        // MUTATIE
        cout<<"\nProbabilitatea de mutatie este " << probMutation<<endl;

        cout <<"\nS-au mutat cromozomii:\n";
        for(i = 0 ; i < popSize ; i++)
        {
            bool mutat = false;
            for(j = 0 ; j < crSize ; j++)
            {
                double u = distribution(generator);

                if(u < probMutation)
                {
                    mutat = true;
                    urmGen[i].data[j] = !urmGen[i].data[j];
                }
            }

            if(mutat == true)
            {
                cout<<i<<" ";
                calcValueAndFit(urmGen[i]);
            }
        }

        cout<<"\nDupa mutatie:\n";
        printCromozomes(urmGen);

        cout<<"Valori maxime si medii:\n";

        cout<<"0. "<<findMax(Cr)<<" " << findAvg(Cr);
        cout<<"\n1. "<<findMax(urmGen)<<" " << findAvg(urmGen)<<endl;

        for(i = 2 ; i < etape ; i++)
        {
            urmGen = urmGeneratie(urmGen);
           /* for(j = 0 ; j < popSize ; j++)
                {
                    for(int k = 0 ; k < crSize ; k++)
                        urmGen[j].data[k] = v[j].data[k];

                    urmGen[j].fit = v[j].fit;
                    urmGen[j].prob = v[j].prob;
                    urmGen[j].value = v[j].value;
                }
            */
            cout<<i<<" "<<findMax(urmGen)<<" "<<findAvg(urmGen)<<endl;
        }
    return 0;
}