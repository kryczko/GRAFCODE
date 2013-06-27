/*This code intends to go through a LOCPOT file produced by vasp and plot the electrostatic potential as a function of z*/


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <stdlib.h>

using namespace std;

double max(double array[], int length)
{
	double start = array[0];
	for (int i = 1; i < length; i ++)
	{
		if (array[i] > start)
		{
			start = array[i];
		}
	}
return start;
}


int main()
{

string infile;
ifstream inputfile;
ofstream outputfile;

double zlattice;
char sd;
cout << "Please enter the inputfile: ";
cin >> infile;
cout << "Selective dynamics? (y or n): ";
cin >> sd;
cout << "Please enter the lattice constant in the z-direction: ";
cin >> zlattice;
cout << "\n##### CODE RUNNING, PLEASE WAIT A MOMENT #####\n\n";


inputfile.open(infile.c_str());
outputfile.open("esp_vs_z.dat");

if (sd == 'n')
{
vector <string> stuff;
string words;
vector <double> good;
double values;
int count = 0, noa, realstart(100000);
while(!inputfile.eof())
{
	inputfile >> words;
	stuff.push_back(words);
	
	if (count == 11)
	{
		noa = atoi (words.c_str());
		realstart = count + noa*3 + 2; // for no selective dynamics
		
	}

	if (count >= realstart)
	{
		values = atof ( words.c_str() );	
		good.push_back(values);
		//cout << "The data file should start here!\n";

	}
	count ++;
}


int nx = good[0], ny = good[1], nz = good[2];

good.erase(good.begin());
good.erase(good.begin());
good.erase(good.begin());


double sum = 0, esp[nz];

int counter = 0;	
for (int i = 0; i < good.size(); i ++)
{
	sum += good[i];
	
	if (i != 0 && i % (nx*ny)  == 0) 
	{
		if (i == nx*ny)
		{
		esp[counter] = (sum - good[i - 1])/(nx*ny);
		counter ++;
		sum = 0;
		}
		else
		{
		esp[counter] = sum/(nx*ny);
                counter ++;
                sum = 0;
		}
	}
} 
double increment = 0;
	
for (int i = 0; i < nz; i ++)
{
	increment += zlattice/nz;	
	outputfile << increment  << "\t" <<  esp[i] << endl; 
}
cout << "The vacuum energy is " << max(esp, nz) << " eV." << endl;

}	

// Selective dynamics option

if (sd == 'y')
{
vector <string> stuff;
string words;
vector <double> good;
double values;
int count = 0, noa, realstart(100000);
while(!inputfile.eof())
{
        inputfile >> words;
        stuff.push_back(words);

        if (count == 11)
        {
                noa = atoi (words.c_str());
                realstart = count + noa*3 + 4; // for no selective dynamics
                
        }

        if (count >= realstart)
        {
                values = atof ( words.c_str() );
                good.push_back(values);
                //cout << "The data file should start here!\n";
    
        }
        count ++;
}   
    
    
int nx = good[0], ny = good[1], nz = good[2];

good.erase(good.begin());
good.erase(good.begin());
good.erase(good.begin());


double sum = 0, esp[nz];

int counter = 0;
for (int i = 0; i < good.size(); i ++)
{
        sum += good[i];

        if (i != 0 && i % (nx*ny)  == 0)
        {
                if (i == nx*ny)
                {
                esp[counter] = (sum - good[i - 1])/(nx*ny);
                counter ++;
                sum = 0;
                }
                else
                {
                esp[counter] = sum/(nx*ny);
                counter ++;
                sum = 0;
                }
        }
}
double increment = 0;
for (int i = 0; i < nz; i ++)
{
        increment += zlattice/nz;
        outputfile << increment  << "\t" <<  esp[i] << endl;
}

cout << "The vacuum energy is " << max(esp, nz) << " eV." << endl;
}
cout << "The data has been placed in \"esp_vs_z.dat\" and can now easily be plotted with gnuplot." << endl;

inputfile.close();
outputfile.close();
return 0;
}
