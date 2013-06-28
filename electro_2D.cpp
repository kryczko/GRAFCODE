/*This code intends to go through a LOCPOT file produced by vasp and plot the electrostatic potential contour as a function of y and z*/


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

double zlattice,ylattice;
char sd;
cout << "Please enter the inputfile: ";
cin >> infile;
cout << "Please enter the lattice constant in the y-direction: ";
cin >> ylattice;
cout << "Please enter the lattice constant in the z-direction: ";
cin >> zlattice;
cout << "\n##### CODE RUNNING, PLEASE WAIT A MOMENT #####\n\n";


inputfile.open(infile.c_str());
outputfile.open("esp_vs_yz.dat");

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
		realstart = count + noa*3 + 2; 
		
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


double sum = 0, esp[nz*ny];

int counter = 0;	
for (int i = 0; i < good.size(); i ++)
{
	sum += good[i];
	
	if (i != 0 && i % (nx)  == 0) 
	{
		if (i == nx)
		{
		esp[counter] = (sum - good[i - 1])/(nx);
		counter ++;
		sum = 0;
		}
		else
		{
		esp[counter] = sum/(nx);
                counter ++;
                sum = 0;
		}
	}
} 
double zincrement = 0, yincrement = 0;
	
for (int i = 0; i < nz; i ++)
{
	zincrement += zlattice/nz;
	yincrement = 0;
	for (int j = 0; j < ny; j ++)
	{	
	yincrement += ylattice/ny;
	outputfile << yincrement  << "\t" <<  zincrement << "\t" << esp[j + i*ny] << endl;
	} 
}
cout << "The vacuum energy is " << max(esp, nz*ny) << " eV." << endl;

	

cout << "The data has been placed in \"esp_vs_yz.dat\" and can now be plotted with matplotlib." << endl;

inputfile.close();
outputfile.close();
return 0;
}
