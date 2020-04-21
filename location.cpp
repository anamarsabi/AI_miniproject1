/**
 * @file location.cpp
 * @author Ana Martínez Sabiote
 *         Isabel Carnoto
 */

#include"location.h"

#include <sstream>


using namespace std;

/**
 * @brief A* algorithm for solving pizza delivery problem
 * @param mapa List of locations. It is modified ES MODIFICADO
 * @param c Origin location
 * @return Order of visit of the locations
 */
queue<location> route(vector<location> &dlist, const location c);

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

/**
 * @brief Splits a string and stores it in a vector
 */
vector<string> splitStrings(string str, char dl);

//int main(int argc, char*argv[])
//{

int main(){
    /*if (argc!=2) {
		cerr<<"Error en el número de argumentos:\n";
		cerr<<"./location <fichero>\n";
		exit(-1);
	}*/
	//vector<location> lista = FromFile(argv[1]); //All locations
	
	//AQUI ESTOY METIENDO ALGO QUE HAY QUE QUITAR
	//We have to create an array of e (edges) with coordinates
    
    int size =13;
    
    vector<location> lista(size);
    
    lista[0].x=0;
    lista[0].y=0;
    lista[0].node=0;

    int x0even=50;
    int x0uneven=0;
    int y0=-50;
    int j=1;

        for(int i=1;i<13;i++){

            if(j%2!=0){
            lista[i].x=x0even;
            lista[i].y=(j-1)*y0;
            x0even=x0even+100;
            }

            if(j%2==0){
            lista[i].x=x0uneven;
            lista[i].y=(j-1)*y0;
            x0uneven=x0uneven+100;

            }

            lista[i].node=i;

            if((i==2)||(i==5)||(i==7)||(i==10)){
                j++;
                x0even=50;
                x0uneven=0;
            }
        };

    for(int k=0; k<13;k++){

        cout<<k<<": x: "<<lista[k].x<<", y: "<<lista[k].y<<endl;
    };
	//AQUI SE ACABA
	
	vector<location> mapa;  //Locations where we want to go
	queue<location> final_route;    //Route of intersections to follow
	string fichero;

    cout<<"Specify locations where to go\n Example of input: 2-5-8-14-22 enter"<<endl;
    string input;
    vector<int> nodes;
    cin>>input;
    
    //INSERTAR FUNCION ISABEL QUE ROMPE UN STRING EN UN VECTOR DE INTS
    
    vector<string> snodes;
    snodes = splitStrings(input, '-');
    
    //Transforming from vector<string> to vector<int>
    
    for(size_t k=0;k<snodes.size();k++)
    {
        nodes.push_back(atoi(snodes.at(k).c_str()));
        cout<<nodes.at(k)<<endl;  
    }

    //Filtering input data
    for(size_t k=0;k<nodes.size();k++)
    {
        if (nodes[k]>lista.size())
        {
            cerr<<"Input error. Value out of the limits of the data file"<<endl;
            exit(-1);
        }
    }
    
    
    for (int i=0; i<nodes.size(); i++)
    {
        for (int j=0; j<lista.size(); j++)
        {
            if (nodes[i] == lista[j].node)
                mapa.push_back(lista[j]);
            
        }   
    }
    
    for(size_t k=0;k<mapa.size();k++){
        cout<<k<<" "<<mapa[k].x<<" "<<mapa[k].y<<endl;
    }
    
    //FIltering data
    cout<<"Specify location of the origin as coord_x coord_y"<<endl;
    cout<<"Coord_x and coord_y can only have values that are multiples of 100"<<endl;
    int x,y;
    cin>>x>>y;
    if ((x%100 != 0) || (y%100 != 0))
    {
        cerr<<"Input error. Not apropriate data"<<endl;
        exit(-1);
    }
    location origin(x,y,0);
    cout<<"Generating route starting by the origin: "<<origin<<"..."<<endl;
    
    final_route=route(mapa,origin);
    while(!final_route.empty()){
        cout<<"node: "<<final_route.front().node<<" x: "<<final_route.front().x<<" y: "<<final_route.front().y<<endl;
        final_route.pop();
        
    }
    /*//cout<<"The total distance is: "<<totalDistance(final_route)<<endl;
    cin>>fichero;
    toFile(final_route,fichero);
    */
    
}

queue<location> route(vector<location> &dlist,const location c)
{
    //SORTING
   
    //VECTOR TO STORE SORTED LIST
    vector<location> slist;

    //DEFINING THE FIRST PLACE (PIZZERIA) AS ORIGIN
    slist.push_back(c);
    
    int tamano=dlist.size();

    //SORTING THE VECTOR ACCORDING TO SMALLEST DISTANCES
    for(size_t j=0;j<tamano;j++){

        int mindist=INT_MAX;
        int pos=0;
        int dist=0;

        for(size_t i=0; i<dlist.size();i++){
            dist=d(slist.at(j), dlist.at(i));

            if((dist<=mindist)&&(dist!=0)/*&&(dlist[i].sorted==false)*/){
                mindist=dist;
                pos=i;
            }
            
        };
        slist.push_back(dlist.at(pos));
        //dlist[pos].sorted=true;
        dlist.erase(dlist.begin()+pos);
    }

    
    
    //ADDING THE LAS PLACE (PIZZERIA)
    slist.push_back(c);
    
    //SHOWING THE SORTED LIST
    cout<<"Sorted places"<<endl;
    for(size_t k=0; k<slist.size();k++){

        cout<<k<<": x: "<<slist[k].x<<", y: "<<slist[k].y<<" node: "<<slist[k].node<<endl;
    };
    cout<<endl;

    
    //BORRAR ESTO
   /* queue<location> sq;
    for(size_t k=0; k<slist.size();k++){

        sq.push(slist.at(k));
    }
    
    return sq;*/
    //HASTA AQUI
    
    //TRANSFORMING THE VECTOR INTO A QUEUE
    //queue<location> squeue=toQueue(slist);


    //MOVING

    location temp=slist.at(0);
    //TEMPORARY MOVEMENTS IN EACH DIRECTION
    location tempr;
    location templ;
    location tempu;
    location tempd;
    //squeue.pop();//Eliminating the pizzeria because we are already there
    
    //TEMPORARY VECTORS TO STORE THE DIFFERENT SORTED LISTS
    vector<location> vec=slist;
    /*vector<location> vecr;
    vector<location> vecl;
    vector<location> vecu;
    vector<location> vecd;
    */

    //QUEUE THAT GIVES THE FINAL ROUTE
    queue<location> route;

    //VALUE OF THE OBJECTIVE FUNCTIONS GOING IN DIFFERENT DIRECTIONS
    
    vector<double> obj(4); //0-right, 1- left, 2-up, 3-down
  

    //WEIGHT OF TRAVERSING A STREET
    double w=100;
    int mini;
    double iterations=1;
    bool brk=false;

    cout<<"ESTO ES LO QUE VALE C"<<endl;
    cout<<"x: "<<c.x<<" y: "<<c.y<<endl;
    //TRANSFORMING THE QUEUE BACK TO A VECTOR STARTING FROM [1]
    //vec=toVector(aux);
    
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
 
        //CALCULATING THE OBJECTIVE FUNCTIONS FOR EACH POSSIBLE VERCTOR
        vec.at(0)=tempr;
        obj.at(0)=w*iterations+totalDistance(vec);

        vec.at(0)=templ;
        obj.at(1)=w*iterations+totalDistance(vec);

        vec.at(0)=tempu;
        obj.at(2)=w*iterations+totalDistance(vec);

        vec.at(0)=tempd;
        obj.at(3)=w*iterations+totalDistance(vec);

        cout<<"Objective function going right: "<<obj.at(0)<<endl;
        cout<<"Objective function going left: "<<obj.at(1)<<endl;
        cout<<"Objective function going up: "<<obj.at(2)<<endl;
        cout<<"Objective function going down: "<<obj.at(3)<<endl;

        //CALCULATING THE WAY WITH THE MINIMUM OBJ. FUNCTION
        mini=minimum(obj);
       cout<<"MINI VALE: "<<mini<<endl;
        //SEPARATING CASES OF MOVEMENT
        
        switch(mini){
            
            case 0: //The minimum is going right
                cout<<"entre al caso0"<<endl;
                vec.at(0)=tempr; //This again because it changed earlier
                
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
                temp.x=tempr.x+50;
                temp.y=tempr.y;
                vec.at(0)=temp;
                    
                break;
                
            case 1: //The minimum is going left
                cout<<"entre al caso1"<<endl;
                vec.at(0)=templ;
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
                temp.x=templ.x-50;
                temp.y=templ.y;
                vec.at(0)=temp;
                break;
                
            case 2: //The minimum is going up
                cout<<"entre al caso2"<<endl;
                vec.at(0)=tempu;
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
                temp.x=tempu.x;
                temp.y=tempu.y+50;
                vec.at(0)=temp;
                break;
                
            case 3: //The minimum is going down
                cout<<"entre al caso3"<<endl;
                vec.at(0)=tempd;
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //WE ADD TO THE VECTOR OUT CURRENT POSITION AS FIRST
                temp.x=tempd.x;
                temp.y=tempd.y-50;
                vec.at(0)=temp;
                
                break;
                
        }

        //ADDING OUT CURRENT POSITION TO THE FINAL ROUTE
        route.push(vec.at(0));
        
        cout<<"List of current and future locations to visit"<<endl;
        for(size_t k=0; k<vec.size();k++){

            cout<<k<<": x: "<<vec.at(k).x<<", y: "<<vec.at(k).y<<endl;
        };

        //BREAK CONDITION !!!!!!! DONT KNOW IF ITS ALWAYS RIGHT!!!!!
        if((vec.at(0).x==c.x)&&(vec.at(0).y==c.y)&&(vec.at(1).x==c.x)&&(vec.at(1).y==c.y)){
            brk=true;
        }
        iterations++;
        
        //}while(iterations<8);
    }while(brk==false);
    
    return route;
    
}

/*
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
*/
vector<string> splitStrings(string str, char dl)
{
    //CODE FROM https://www.geeksforgeeks.org/split-string-substrings-using-delimiter/
    string word = "";

    // to count the number of split strings
    int num = 0;

    // adding delimiter character at the end
    // of 'str'
    str = str + dl;

    // length of 'str'
    int l = str.size();

    // traversing 'str' from left to right
    vector<string> substr_list;
    for (int i = 0; i < l; i++) {

        // if str[i] is not equal to the delimiter
        // character then accumulate it to 'word'
        if (str[i] != dl)
            word = word + str[i];

        else {

            // if 'word' is not an empty string,
            // then add this 'word' to the array
            // 'substr_list[]'
            if ((int)word.size() != 0)
                substr_list.push_back(word);

            // reset 'word'
            word = "";
        }
    }

    // return the splitted strings
    return substr_list;
}
