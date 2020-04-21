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
vector<location> FromFile(char* fichero);

/**
 * @brief Splits a string and stores it in a vector
 */
vector<string> splitStrings(string str, char dl);

//int main(int argc, char*argv[])
//{

int main(int argc, char*argv[]){
    if (argc!=3) {
		cerr<<"Error en el número de argumentos:\n";
		cerr<<"./location <fichero_data> <fichero_salida>\n";
		exit(-1);
	}
	vector<location> lista = FromFile(argv[1]); //All locations
    string fichero = argv[2]; //Output file
	vector<location> mapa;  //Locations where we want to go
	queue<location> final_route;    //Route of intersections to follow

    cout<<"Specify locations where to go\n Example of input: 2-5-8-14-22 enter"<<endl;
    string input;
    vector<int> nodes;
    cin>>input;
    
    vector<string> snodes;
    snodes = splitStrings(input, '-');
    
    //Transforming from vector<string> to vector<int>
    
    for(size_t k=0;k<snodes.size();k++)
    {
        nodes.push_back(atoi(snodes.at(k).c_str()));
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
    
    //Creating the vector of locations to visit
    for (int i=0; i<nodes.size(); i++)
    {
        for (int j=0; j<lista.size(); j++)
        {
            if (nodes[i] == lista[j].node)
                mapa.push_back(lista[j]);
            
        }   
    }
    cout<<endl;
    cout<<"List of Delivery Locations"<<endl;
    
    for(size_t k=0;k<mapa.size();k++){
        cout<<k<<". x: "<<mapa[k].x<<", y: "<<mapa[k].y<<endl;
    }
    
    //Filtering data
    cout<<endl;
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
    cout<<endl;
    cout<<"Generating route starting by the origin: "<<origin<<"..."<<endl;
    
    final_route=route(mapa,origin);
    toFile(final_route,fichero);
    cout<<endl;
    
    cout<<"List of nodes visited"<<endl;
    
    while(!final_route.empty()){
        cout<<"x: "<<final_route.front().x<<", y: "<<final_route.front().y<<endl;
        final_route.pop();
        
    }
    cout<<"List of nodes saved in "<<fichero<<" file"<<endl;
}

queue<location> route(vector<location> &dlist,const location c)
{
    //SORTING
   
    //Vector to store the sorted list
    vector<location> slist;

    //Defining the first place as origin (pizzeria)
    slist.push_back(c);
    
    int tamano=dlist.size();

    //Sorting the vector according to the smaller distances
    for(size_t j=0;j<tamano;j++){

        int mindist=INT_MAX;
        int pos=0;
        int dist=0;

        for(size_t i=0; i<dlist.size();i++){
            dist=d(slist.at(j), dlist.at(i));

            if((dist<=mindist)&&(dist!=0)){
                mindist=dist;
                pos=i;
            }
            
        };
        slist.push_back(dlist.at(pos));
        dlist.erase(dlist.begin()+pos);
    }

    
    //Adding the origin as last location
    slist.push_back(c);
    
    //Showing the sorted locations
    cout<<endl;
    cout<<"List of delivery locations in order:"<<endl;
    for(size_t k=0; k<slist.size();k++){

        cout<<k<<". x: "<<slist[k].x<<", y: "<<slist[k].y<<", node: "<<slist[k].node<<endl;
    };


    //MOVING

    location temp=slist.at(0);
    //Temporary movements in each direction
    location tempr;
    location templ;
    location tempu;
    location tempd;
        
    //Temporary vector<location>
    vector<location> vec=slist;

    //Queue that gives the final route
    queue<location> route;
    route.push(temp);

    //Value of the objective function going in different directions
    
    vector<double> obj(4); //0-right, 1- left, 2-up, 3-down
  

    //Weight of traversing a street
    double w=100;
    
    int mini;
    double iterations=1;
    bool brk=false;
    
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
        
        //Chosing the direction with the smallest objective function
        mini=minimum(obj);
       
        //SEPARATING CASES OF MOVEMENT
        
        switch(mini){
            
            case 0: //The minimum is going right
                
                vec.at(0)=tempr; //This again because it changed earlier
                
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //We add to the vector out current position as first
                temp.x=tempr.x+50;
                temp.y=tempr.y;
                vec.at(0)=temp;
                    
                break;
                
            case 1: //The minimum is going left
                
                vec.at(0)=templ;
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //We add to the vector out current position as first
                temp.x=templ.x-50;
                temp.y=templ.y;
                vec.at(0)=temp;
                break;
                
            case 2: //The minimum is going up
                
                vec.at(0)=tempu;
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //We add to the vector out current position as first
                temp.x=tempu.x;
                temp.y=tempu.y+50;
                vec.at(0)=temp;
                break;
                
            case 3: //The minimum is going down
                
                vec.at(0)=tempd;
                if((vec.at(0).x==vec.at(1).x)&&(vec.at(0).y==vec.at(1).y)){
                    //
                    vec.erase(vec.begin());
                }
                //We add to the vector out current position as first
                temp.x=tempd.x;
                temp.y=tempd.y-50;
                vec.at(0)=temp;
                
                break;
                
        }

        //Adding our current position to the final route
        route.push(vec.at(0));

        if((vec.at(0).x==c.x)&&(vec.at(0).y==c.y)&&(vec.at(1).x==c.x)&&(vec.at(1).y==c.y)){
            
            brk=true;
        }
        iterations++;
        
    }while(brk==false);
    
    return route;
    
}


void toFile(queue<location> r,string fichero)
{
    fstream fout;
	
	fout.open(fichero.c_str());
	if (fout) {
        
		while (!r.empty()) {
			fout<<r.front().x<<" "<<r.front().y<<endl;
			r.pop();
		}
	} else
		cerr<<"Error in capturing the file\n";
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
        cerr<<"File not found"<<endl;
        exit(-1);
    }
}

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
