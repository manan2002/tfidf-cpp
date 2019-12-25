#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<utility>
#include<cstdio>
#include "summarizer.h"

using namespace std;

class data{

        string paragraph;
        vector<pair<int, double>> summary;

        
        vector<string> returnSentences(); 
        
        void assignSummary(){
            summary = getSummary(paragraph);
        }

    public:    
        //Constructors
        data(string para){
            paragraph = para;
            assignSummary();
        }
        data(){
            paragraph = "Not yet set";
        }


        //Public functions.
        vector<pair<int, double>> returnSummary(); 
        
        string returnParagraph();  
        
        void displaySummary(){
            vector<string> sentences = returnSentences(); 
            assignSummary();
            int numlines = 4, count = 0;
            for(auto x: summary){
                cout<<sentences[x.first]<<"\n\n";
                if(count >= numlines) break;
                count++;
            }
        }
};

vector<string> data::returnSentences(){
    return getSentences(paragraph);
}

vector<pair<int, double>> data::returnSummary(){  
    return summary;
}

string data::returnParagraph(){
    return paragraph;
}

int main(){

//    fstream f("data.dat", ios::in | ios::out | ios::binary);
    data d("Pollution in Delhi is a perpetual problem which need to be looked upon as a serious issue not only by the Government but also by the citizens of the city.One of the easiest ways is that there should be an efficient involvement of Resident Welfare Associations in various localities in collection, segregation of garbage from houses and the societies.Citizens can take steps to covert the garbage into compost in their localities.More and more trees must be planted in every locality.Every individual should keep a proper check on the pollution level of their vehicles.Making more use of CNG.One of the best ways to control pollution is to manage wastes of all types in a proper manner.Each and every citizen should abide by the 3Rs: Recycle, Reuse, Reduce.More and more people should use bus and metro instead of cars and scooters, as they can carry a lot more people in one journey. Car pool is also a good option.Controlling the use of energy and making use of electricity in an efficient manner.One can also reduce water pollution by reducing the use of chemicals, cleaning agents, pesticides, herbicides, fertilizers etc.It is the duty of every citizen to think in a broader perspective to control pollution. We really don’t want our future generations to live in an unhealthy environment in Delhi. We really don’t want our children or our elders to get into incessant coughing due to pollution. Like we say charity begins at home, I take a pledge to do what I can for my environment and protect it to the best I can. If each one of us takes a pledge to do our bit for our environment, I am sure Delhi will be a better place to live in. Even asmall step counts.");

    remove("data.dat");
    ofstream of("data.dat", ios::app | ios::binary);
    if(!of){
        cout<<"can't create file.\n";
    }else{
        of.write((char*)&d, sizeof(d));
        cout<<"Written to file.\n";
        of.close();
    }
    ifstream fin("data.dat", ios::in | ios::binary);
    data d1;
    cout<<d1.returnParagraph()<<"\n\n";
    fin.read((char*)&d1, sizeof(d1));
    cout<<d1.returnParagraph()<<"\n\n";
    d1.displaySummary();
    
}
