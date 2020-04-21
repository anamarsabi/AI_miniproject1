/**
 * @file location.h
 * @author Ana Martínez Sabiote
 *         Isabel Carnoto
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include<fstream>
#include<queue>
#include<vector>
#include<string>
#include<time.h>
#include<climits>

using namespace std;

#ifndef _LOCATION_H
#define _LOCATION_H

struct location
{
    double x; ///< Coordinate x
    double y; ///< Coordinate y
    int node;
    
	/**
	 * @brief Constructor
	 */
    location()
    {
        x=0;
        y=0;
        node=0;
        

    }

    location(double a,double b, int node_) 
    {
        x=a;
        y=b;
        node=node_;
        
    }

    location(const location &a)
    {
        x=a.x;
        y=a.y;
        node=a.node;
        
    }
};

/**
 * @brief Creates a list of cities from a given file
 */
vector<location> FromFile(string fichero);

/**
 * @brief Input overloding operator for Location
 */
istream & operator >>(istream & is, location & c);

/**
 * @brief Output overloading operator for Location
 */
ostream & operator <<(ostream & os, location & c);

/**
 * @brief returns distance between two locations
 */
double d(location a, location b);

/**
 * @brief Calculates the sum of distences  between all the cities of a list
 */
double totalDistance(vector<location> &v);

/**
 * @brief Finds the minimum in a vector 
 */
int minimum(vector<double> &v);


//IMPLEMENTATION
istream & operator >>(istream & is, location & c) 
{
    double x;
    double y; 
    int node;

    is >> node;
    is >> x;
    is >> y;

    c.x=x;
    c.y=y; 
    c.node=node;

    return is;
}

ostream & operator <<(ostream & os, location & c) 
{
	os<<"("<<c.x<<","<<c.y<<")";
	return os;
}


double d(location a, location b) 
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

double totalDistance(vector<location> &v) 
{
    double sum = 0;
    for(size_t i=0;i<v.size()-1;i++) 
    {
        sum += d(v[i],v[i+1]);

    }
    return sum;
}

int minimum(vector<double> &v)
{
    double mini=v.at(0);
    int pos=0;
    
    for(int i=1; i<v.size();i++){
    
        if(v.at(i)<mini){
            mini=v.at(i);
            pos=i;
        }
    }
    
    return pos;
}

#endif


