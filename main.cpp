#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<string>
#include<time.h>

using namespace std;
struct location{
    double x; ///< Coordinate x
    double y; ///< Coordinate y
    int node;
    bool sorted;
	/**
	 * @brief Constructor
	 */
    location(){
        x=0;
        y=0;
        node=0;
        sorted=false;

    }
    location(double a,double b, int node_, bool sorted_) {
        x=a;
        y=b;
        node=node_;
        sorted=sorted_;
    }
    location(const location &a){
        x=a.x;
        y=a.y;
        node=a.node;
        sorted=a.sorted;
    }
};

double d(location a, location b) {
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
};



double totalDistance(vector<location> &v) {
    double sum = 0;
    for(size_t i=0;i<v.size()-1;i++) {
        sum += d(v[i],v[i+1]);

    }
    return sum;
}

queue<location> toQueue(vector<location> &v){
    queue<location> r;
    for(size_t k=0; k<v.size();k++){

        r.push(v[k]);
    };
    return r;
}

//THIS FUNCTION TRANSFORMS FROM QUEUE TO VECTOR STARTING FROM INDEX 1
vector<location> toVector(queue<location> &v){
    vector<location> aux(v.size()+1);
    int k=1;
    while(!v.empty()){
        aux[k]=v.front();
        v.pop();
        k++;
    }
    return aux;
}

double minimum(double a, double b, double c, double d){
    double mini=INT_MAX;
    double aray[4]={a, b, c, d};

    for(int i=0; i<4;i++){
        if(aray[i]<mini){
            mini=aray[i];
        }
    }

    return mini;
}

	int main (){

    //We have to create an array of e (edges) with coordinates
    struct location edges[13];
    edges[0].x=0;
    edges[0].y=0;
    edges[0].node=0;

    int x0even=50;
    int x0uneven=0;
    int y0=-50;
    int j=1;

        for(int i=1;i<13;i++){

            if(j%2!=0){
            edges[i].x=x0even;
            edges[i].y=(j-1)*y0;
            x0even=x0even+100;
            }

            if(j%2==0){
            edges[i].x=x0uneven;
            edges[i].y=(j-1)*y0;
            x0uneven=x0uneven+100;

            }

            edges[i].node=i;

            if((i==2)||(i==5)||(i==7)||(i==10)){
                j++;
                x0even=50;
                x0uneven=0;
            }
        };

    for(int k=0; k<13;k++){

        cout<<k<<": x: "<<edges[k].x<<", y: "<<edges[k].y<<endl;
    };

    vector<location> dlist = {edges[6], edges[5], edges[12]};
    cout<<"Delivery places"<<endl;

    for(size_t i=0; i<dlist.size();i++){

    cout<<": x: "<<dlist[i].x<<", y: "<<dlist[i].y<<" node: "<<dlist[i].node<<endl;

    }
    cout<<endl;
    //SORTING

    //VECTOR TO STORE SORTED LIST
    vector<location> slist(dlist.size()+2);

    //DEFINING THE FIRST PLACE (PIZZERIA) AS 0,0
    slist[0].x=0;
    slist[0].y=0;
    slist[0].node=0;

    //SORTING THE VECTOR ACCORDING TO SMALLEST DISTANCES

    int pos;
    int dist;
    int mindist;

    for(size_t j=0;j<dlist.size()+1;j++){

        mindist=INT_MAX;
        pos=0;
        dist=0;

        for(size_t i=0; i<dlist.size();i++){
            dist=d(slist[j], dlist[i]);

            if((dist<=mindist)&&(dist!=0)&&(dlist[i].sorted==false)){
                mindist=dist;
                pos=i;
            }
        };
        slist[j+1]=dlist[pos];
        dlist[pos].sorted=true;
    }

    //ADDING THE LAS PLACE (PIZZERIA)
    slist[slist.size()-1]=slist[0];

    //SHOWING THE SORTED LIST
    cout<<"Sorted places"<<endl;
    for(size_t k=0; k<slist.size();k++){

        cout<<k<<": x: "<<slist[k].x<<", y: "<<slist[k].y<<" node: "<<slist[k].node<<endl;
    };
    cout<<endl;

    //TRANSFORMING THE VECTOR INTO A QUEUE
    queue<location> squeue=toQueue(slist);


    //MOVING

    location temp=squeue.front();
    //TEMPORARY MOVEMENTS IN EACH DIRECTION
    location tempr;
    location templ;
    location tempu;
    location tempd;
    squeue.pop();//Eliminating the pizzeria because we are already there

    //TEMPORARY VECTORS TO STORE THE DIFFERENT SORTED LISTS
    vector<location> vec;
    vector<location> vecr;
    vector<location> vecl;
    vector<location> vecu;
    vector<location> vecd;

    //QUEUE THAT GIVES THE FINAL ROUTE
    queue<location> route;

    //TEMPORARY QUEUES
    queue<location> tq;
    queue<location> aux=squeue;

    //VALUE OF THE OBJECTIVE FUNCTIONS GOING IN DIFFERENT DIRECTIONS
    double objr;
    double objl;
    double obju;
    double objd;

    //WEIGHT OF TRAVERSING A STREET
    double w=100;

    double num=1;
    int index=0;
    double mini;
    bool brk=false;

    //TRANSFORMING THE QUEUE BACK TO A VECTOR STARTING FROM [1]
    vec=toVector(aux);

    do{

        //temporary location to the right
        tempr.x=temp.x +50;
        tempr.y=temp.y;

        //temporary location to the left
        templ.x=temp.x -50;
        templ.y=temp.y;

        //temporary location up
        tempu.x=temp.x;
        tempu.y=temp.y+50;

        //temporary location down
        tempd.x=temp.x;
        tempd.y=temp.y-50;

        //TEMPORARY VECTORS THAT EACH HAVE AS [0] THE TEMPORARY MOVEMENT AND THE REST
        //IS THE REMAINING OF THE SORTED LIST
        vecr=vec;
        vecr[0]=tempr;

        vecl=vec;
        vecl[0]=templ;

        vecu=vec;
        vecu[0]=tempu;

        vecd=vec;
        vecd[0]=tempd;

        //CALCULATING THE OBJECTIVE FUNCTIONS FOR EACH POSSIBLE VERCTOR
        objr=w*num+totalDistance(vecr);
        objl=w*num+totalDistance(vecl);
        obju=w*num+totalDistance(vecu);
        objd=w*num+totalDistance(vecd);

        cout<<"Objective function going right: "<<objr<<endl;
        cout<<"Objective function going left: "<<objl<<endl;
        cout<<"Objective function going up: "<<obju<<endl;
        cout<<"Objective function going down: "<<objd<<endl;

    //CALCULATING THE WAY WITH THE MINIMUM OBJ. FUNCTION
    mini=minimum(objr, objl, obju, objd);

    //SEPARATING CASES OF MOVEMENT


    if(mini==objr){//RIGHT IS THE SMALLEST

        if((vecr[0].x==vecr[1].x)&&(vecr[0].y==vecr[1].y)){
        //IF WE ARE ALREADY AT THE CORRESPONDING E WE POP IT OUT OF THE QUEUE
        tq=toQueue(vecr);
        tq.pop();
        tq.pop();
        squeue=tq;
        vecr=toVector(tq);

        }
        //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
        temp.x=tempr.x+50;
        temp.y=tempr.y;
        vecr[0]=temp;
        vec=vecr;

    }
    else if(mini==objl){ //LEFT IS THE SMALLEST
        if((vecl[0].x==vecl[1].x)&&(vecl[0].y==vecl[1].y)){
        //IF WE ARE ALREADY AT THE CORRESPONDING E WE POP IT OUT OF THE QUEUE
        tq=toQueue(vecl);
        tq.pop();
        tq.pop();
        squeue=tq;
        vecl=toVector(tq);

        }
        //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
        temp.x=templ.x-50;
        temp.y=templ.y;
        vecl[0]=temp;
        vec=vecl;
    }
    else if(mini==obju){//UP IS THE SMALLEST
        if((vecu[0].x==vecu[1].x)&&(vecu[0].y==vecu[1].y)){
        //IF WE ARE ALREADY AT THE CORRESPONDING E WE POP IT OUT OF THE QUEUE
        tq=toQueue(vecu);
        tq.pop();
        tq.pop();
        squeue=tq;
        vecu=toVector(tq);

        }
        //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
        temp.x=tempu.x;
        temp.y=tempu.y+50;
        vecu[0]=temp;
        vec=vecu;
    }
    else if(mini==objd){//DOWN IS THE SMALLEST
        if((vecd[0].x==vecd[1].x)&&(vecd[0].y==vecd[1].y)){
        //IF WE ARE ALREADY AT THE CORRESPONDING E WE POP IT OUT OF THE QUEUE
        tq=toQueue(vecd);
        tq.pop();
        tq.pop();
        squeue=tq;
        vecd=toVector(tq);

        }
        //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
        temp.x=tempd.x;
        temp.y=tempd.y-50;
        vecd[0]=temp;
        vec=vecd;
    }


    cout<<"List of current and future locations to visit"<<endl;
    for(size_t k=0; k<vec.size();k++){

        cout<<k<<": x: "<<vec[k].x<<", y: "<<vec[k].y<<endl;
    };

    //ADDING OUT CURRENT POSITION TO THE FINAL ROUTE
    route.push(vec[0]);

    //BREAK CONDITION !!!!!!! DONT KNOW IF ITS ALWAYS RIGHT!!!!!
    if((vec[0].x==0)&&(vec[0].y==0)&&(vec[1].x==0)&&(vec[1].y==0)){
        brk=true;
    }
    index++;
    num++;
    }while(brk==false);

    //PRINTING OUT THE FINAL ROUTE
    cout<<"ROUTE "<<endl;
    while(!route.empty()){

        cout<<": x: "<<route.front().x<<", y: "<<route.front().y<<endl;
        route.pop();
    };


    return 0;
}
