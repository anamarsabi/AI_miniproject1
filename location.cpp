/**
 * @file location.cpp
 * @author Ana Martínez Sabiote
 *         Isabel Carnoto
 */

#include"location.h"

using namespace std;

/**
 * @brief A* algorithm for solving pizza delivery problem
 * @param mapa List of locations. It is modified ES MODIFICADO
 * @param c Origin location
 * @return Order of visit of the locations
 */
queue<location> route(vector<location> &v,const location &c);

/**
 * @brief Shows the way
 * @param r Way to show
 * @param fichero File "fichero" where it is saved
 */
void toFile(queue<location> r,string fichero);

/**
 * @brief Creates a list of locations from a given file
 */
vector<location> FromFile(string fichero);


int main(int argc, char*argv[])
{
    if (argc!=2) {
		cerr<<"Error en el número de argumentos:\n";
		cerr<<"./location <fichero>\n";
		exit(-1);
	}
	vector<location> lista = FromFile(argv[1]); //All locations
	vector<location> mapa;  //Locations where we want to go
	queue<location> final_route;    //Route of intersections to follow
	string fichero;

    cout<<"Specify locations where to go\n Example of input: 2-5-8-14-22 enter"<<enld;
    string input;
    vector<int> nodes;
    cin>>input;
    //INSERTAR FUNCION ISABEL QUE ROMPE UN STRING EN UN VECTOR DE INTS
    for (int i=0; i<nodes.size(); i++)
    {
        for (int j=0; j<lista.size(); j++)
        {
            if (nodes[i] == lista[j].node)
                mapa.push_back(lista[j]);
        }
    }
    cout<<"Specify location of the origin: ";
    int n,x,y;
    cin>>n>>x>>y;
    location origin(x,y,n);
    cout<<"Generating route starting by the origin: "<<origin<<"..."<<endl;
    final_route=route(mapa,origin);
    //cout<<"The total distance is: "<<totalDistance(final_route)<<endl;
    cin>>fichero;
    toFile(final_route,fichero);
}

queue<location> route(vector<location> &dlist,const location &c)
{
    //SORTING

    //VECTOR TO STORE SORTED LIST
    vector<location> slist();

    //DEFINING THE FIRST PLACE (PIZZERIA) AS ORIGIN
    slist.push_back(c);

    //SORTING THE VECTOR ACCORDING TO SMALLEST DISTANCES
    for(size_t j=0;j<dlist.size()+1;j++){

        int mindist=INT_MAX;
        int pos=0;
        int dist=0;

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
    slist.push_back(c);

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
    
    return route;
}

void toFile(queue<location> r,string fichero)
{
    fstream fout;
	
	fout.open(fichero);
	if (fout) {
		while (!r.empty()) {
			fout<<r.front().node<<" "<<r.front().x<<" "<<r.front().y<<endl;
			r.pop();
		}
	} else
		cerr<<"Error en la apertura del fichero\n";
}

vector<location> FromFile(char *fichero) {
    ifstream fin;
    string numerillo;

    fin.open(fichero);
    if(fin){
        getline(fin,numerillo);
        int dim = atoi(numerillo.c_str());

        int indice = 0;
        location aux(0,0,0);
        vector<location> v;
        
        while(indice < dim){
            fin>>aux;
            v.push_back(aux);
            indice++;
        }
        return v;
    }
    else{
        cerr<<"Archivo no encontrado"<<endl;
        exit(-1);
    }
}

