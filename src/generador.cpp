#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <vector>
#include <chrono>
#include"location.h"
using namespace std;

/* Data generator for the problem of pizza delivery.
    It generates coordinates:
    Case 1: x multiple of 50 but not multiple of 100
            y multiple of 100
    Case 2: x multiple of 100
            y multiple of 50
*/
 

void toFile(queue<location> r,string fichero)
{
    fstream fout;
	
	fout.open(fichero.c_str());
	if (fout) {
		while (!r.empty()) {
			fout<<r.front().node<<" "<<r.front().x<<" "<<r.front().y<<endl;
			r.pop();
		}
	} else
		cerr<<"Error en la apertura del fichero\n";
}

int main(int argc, char*argv[])
{

    if (argc!=2) {
		cerr<<"Error en el número de argumentos:\n";
		cerr<<"./generador <fichero>\n";
		exit(-1);
	}
    string fichero=argv[1];
    queue<location> output;
    cout<<"Enter how many data you wish to create: ";
    int num = 0;
    cin>>num;

    cout<<"Enter limits of the coordinates: ";
    int lim=0;
    cin>>lim;
    if (((lim/150)*6)<num)
        cerr<<"Error, limit too low"<<endl;

    srand(time(NULL));
    int xaux, yaux, x, y;

    //Horizontal coordinates
    for (int i=0; i<num/2; i++)
    {
        do
        {
            x = 50*((rand())%num/2);
        }
        while (x%100 == 0);
        y = 100*((rand())%num/2);
        location aux(x,y,i);
        output.push(aux);
    }
    for (int i=0; i<num/2; i++)
    {
        do
        {
            y = 50*((rand())%num/2);
        }
        while (y%100 == 0);
        x = 100*((rand())%num/2);
        location aux(x,y,i+num/2);
        output.push(aux);
    }
    cin>>fichero;
    toFile(output,fichero);
}
