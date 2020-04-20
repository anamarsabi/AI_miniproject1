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
    bool sorted;
	/**
	 * @brief Constructor
	 */
    location()
    {
        x=0;
        y=0;
        node=0;
        sorted=false;

    }

    location(double a,double b, int node_) 
    {
        x=a;
        y=b;
        node=node_;
        sorted=false;
    }

    location(const location &a)
    {
        x=a.x;
        y=a.y;
        node=a.node;
        sorted=a.sorted;
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
double d(location a, location b)

/**
 * @brief Calculates the sum of distences  between all the cities of a list
 */
double totalDistance(vector<location> &v)

/**
 * @brief Adds all the elements of the vector passed aas a parameter to a queue
 */
queue<location> toQueue(vector<location> &v)

/**
 * @brief Adds all the elements of the queue passed as a parameter to a vector
 *          starting from index 1
 */
vector<location> toVector(queue<location> &v)

/**
 * @brief Finds the minimum of 4 elements
 */
double minimum(double a, double b, double c, double d)


//IMPLEMENTATION
istream & operator >>(istream & is, ciudad & c) 
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

ostream & operator <<(ostream & os, ciudad & c) 
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

queue<location> toQueue(vector<location> &v)
{
    queue<location> r;
    for(size_t k=0; k<v.size();k++)
    {

        r.push(v[k]);
    };
    return r;
}

vector<location> toVector(queue<location> &v)
{
    vector<location> aux(v.size()+1);
    int k=1;
    while(!v.empty())
    {
        aux[k]=v.front();
        v.pop();
        k++;
    }
    return aux;
}

double minimum(double a, double b, double c, double d)
{
    double mini=INT_MAX;
    double aray[4]={a, b, c, d};

    for(int i=0; i<4;i++)
    {
        if(aray[i]<mini){
            mini=aray[i];
        }
    }

    return mini;
}




