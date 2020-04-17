#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class Location{
    public:
        string name;
        int x;
        int y;
        bool sorted;

    Location(string aname, int ax, int ay, bool asorted){
        name=aname;
        x=ax;
        y=ay;
        sorted=asorted;
    }

    Location(){
        name="x0";
        x=0;
        y=0;
        sorted=false;
    }
};

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

double distance(Location l1, Location l2){
    //if((l1=NULL) || (l2=NULL))
       // return INT_MAX;

return sqrt(pow(l1.x-l2.x,2)+pow(l1.y-l2.y,2));

};

int main()
{

    Location v0("v0", 0, 0, false);
    Location e1("z1", 50, 0, false);
    Location e2("z2", 150, 0, false);
    Location e3("z3", 0, 50, false);
    Location e4("z4", 100, 50, false);
    Location e5("z5", 200, 50, false);
    Location e6("z6", 50, 100, false);
    Location e7("z7", 150, 100, false);
    Location e8("z8", 0, 150, false);
    Location e9("z9", 100, 150, false);
    Location e10("z10", 200, 150, false);
    Location e11("z11", 50, 200, false);
    Location e12("z12", 150, 200, false);

    string input;

    cout<< "Introduce a sequence of locations"<<endl;
    cout<< "please use the format z3-z4-z7"<<endl;

    getline(cin, input);

    cout<<"Your entry is: "<<input<<endl;

    vector<string> input_list = splitStrings(input, '-');

    int totalLocations=12;

    Location allLocations[totalLocations]={e1, e2, e3, e4, e5, e6, e7, e8, e9, e10 ,e11 ,e12};

    Location deliveryList[input_list.size()];

    for(int i=0; i<totalLocations;i++){

        for(int j=0; j< input_list.size();j++){

            if(allLocations[i].name==input_list[j])
                deliveryList[j]=allLocations[i];
        };
    };

    cout<<"delivery list"<<endl;
    for(int k=0; k<input_list.size(); k++){

        cout<<deliveryList[k].name<<endl;

    };

    //SORTING

    Location sortedList[input_list.size()+2];
    sortedList[0]=v0;
    int pos;
    int dist;
    int mindist;

    for(int j=0;j<input_list.size()+1;j++){

        mindist=INT_MAX;
        pos=0;
        dist=0;

        for(int i=0; i<input_list.size();i++){
            dist=distance(sortedList[j], deliveryList[i]);

            if((dist<=mindist)&&(dist!=0)&&(deliveryList[i].sorted==false)){
                mindist=dist;
                pos=i;
            }
        };
        sortedList[j+1]=deliveryList[pos];
        deliveryList[pos].sorted=true;
    }

    sortedList[input_list.size()+1]=v0;

    cout<<"sorted list"<<endl;
    for(int k=0; k<input_list.size()+2; k++){

        cout<<sortedList[k].name<<endl;

    };





    return 0;
}
