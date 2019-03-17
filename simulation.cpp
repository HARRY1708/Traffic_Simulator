#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <list>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>

using namespace std;
using namespace boost;

typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
static const char_separator<char> sep(" ","#");

char** road;
int Road_Id;
int road_length;
int road_width;
bool road_signal;
int default_maxspeed;
int default_acc;
int Simulationtime=500;
bool start_simulation;
bool end_bool;5141
string current;
int vehicle_count=-1;
vector<tuple<string,string,int>> road_vehicle;   //vehicle type,colour,to_wait_for
tuple <string,int,int,int,int,string> list_of_vehicle[10]; //tuple of <name,length,width,speed,acc,colour>
class vehicle{  
 public :
  string type;
  int vehicle_length;
  int vehicle_width;
  int vehicle_speed;
  int vehicle_acc;
  string color;
  bool brake;
  int x1,y1,x2,y2;
  vehicle(string type,string color){
    this->type=type;
    this->color=color;
    this->brake=false;
    int xx=0;
    cout << type;
    cout << get<0>(list_of_vehicle[0]);
    while(get<0>(list_of_vehicle[xx])!=type){
      xx++;
      cout << xx;
    }
          
    
    this->vehicle_length = get<1>(list_of_vehicle[xx]);
    this->vehicle_width = get<2>(list_of_vehicle[xx]);
    this->vehicle_speed = get<3>(list_of_vehicle[xx]);
    this->vehicle_acc = get<4>(list_of_vehicle[xx]);

    this->x1=abs(rand()%(road_width-vehicle_width+1))+1;
    this->y1=-1;
    this->y2=-vehicle_length;
    this->x2=x1+vehicle_width-1;
    }
  int closest_distance(){
    for(int i=y1+1;i<road_length;i++){
      for(int j=x1;j<=x2;j++){
        if(road[j][i]!=' ')
          return (i-y1); 
      }
    }
    return 100000000;
  }
  void update(){
    int cdist =closest_distance()-1;
    y1=y1+min(vehicle_speed,cdist);
    y2=y2+min(vehicle_speed,cdist);
  }
};
vector<vehicle> automobiles;
void make_frame(){
   for(int i=0;i<road_width+2;i++){
      for(int j=0;j<road_length;j++){
        if(i==0||i==road_width+1)
           road[i][j]='-';
          else if(!road_signal&&j==50)
           road[i][j]='|';
          else
            road[i][j]=' ';
        } 
    }
    for(int i=0;i<automobiles.size();i++){
      automobiles[i].update();
      for(int j=automobiles[i].x1;j<=automobiles[i].x2;j++){
        for(int k=max(automobiles[i].y2,0);k<=min(automobiles[i].y1,road_length-1);k++){
          road[j][k]=automobiles[i].type[0];
        }
      }
    }
}
void print_frame(){
   for(int i=0;i<road_width+2;i++){
      for(int j=0;j<road_length;j++){
          cout<<road[i][j];
        }
        cout<<endl;
    }

}

void parseLine(const string &line)
{
  if (line[0] == '#' || line.empty())
    return;
  Tokenizer tokenizer(line, sep);
  vector<string> tokens;
  for (Tokenizer::iterator iter = tokenizer.begin(); iter != tokenizer.end(); iter++)
    tokens.push_back(*iter);
  //cout << tokens[0]<< endl;
  if (tokens[0] == "Road_Id")
      Road_Id= stoi(tokens[2]);
  if (tokens[0] == "Road_Length")
      road_length = stoi(tokens[2]);
  if (tokens[0] == "Road_Width")
      road_width = stoi(tokens[2]);
  if (tokens[0] == "Road_Signal")
      road_signal = stoi(tokens[2]);
  if (tokens[0] == "Default_MaxSpeed")
      default_maxspeed = stoi(tokens[2]);
  if (tokens[0] == "Default_Acceleration")
      default_acc  = stoi(tokens[2]);
  if(tokens[0]== "Vehicle_Type")
  {
      vehicle_count++;
      current = tokens[2];
      get<0>(list_of_vehicle[vehicle_count]) = current;
      get<3>(list_of_vehicle[vehicle_count]) = default_maxspeed;
      get<4>(list_of_vehicle[vehicle_count]) = default_acc;
  }
  if(tokens[0]=="Vehicle_Length")
  {
      get<1>(list_of_vehicle[vehicle_count])= stoi(tokens[2]);
  }
  if(tokens[0]=="Vehicle_Width")
  {
      get<2>(list_of_vehicle[vehicle_count])= stoi(tokens[2]);
  }
  if(tokens[0]=="Vehicle_MaxSpeed")
  {
      get<3>(list_of_vehicle[vehicle_count])= stoi(tokens[2]);
  }
  if(tokens[0]=="Vehicle_Acceleration")
  {
      get<4>(list_of_vehicle[vehicle_count])= stoi(tokens[2]);

  }
  if(tokens[0]=="START")
  {
      road_vehicle.push_back(<"start","start",0>)
  }
  if(tokens[0]="Signal")
  {
    if(tokens[1]="RED"){
      road_vehicle.push_back(<"red","red",0>);
    }
    else
      road_vehicle.push_back(<"green","green",0>); 
  }
  for(int i=0;i<vehicle_count;i++){
    if(tokens[0]==get<0>(list_of_vehicle[i]))
    {
      road_vehicle.push_back(<tokens[0],tokens[1],1>);
    }
  }
  if(tokens[0]="pass"){
    road_vehicle.push_back(<"pass","pass",15>);
  }
  if(tokens[0]="END")
    end_bool=true;

} 


int main(){
    
    ifstream file;
     file.open("config.ini");
 
    if (file.is_open()){
       while(file.good())
       {
          char line[255];
          file.getline(line, 255);
          string linestring(line);
          parseLine(linestring);
       }
    }
     else
     {
          cout << "Unable to open the file" << endl;
          return -2;
     }

   file.close();
   // for(int i=0;i<4;i++){
   //  cout << get<0>(list_of_vehicle[i])<< " " << get<1>(list_of_vehicle[i]) << " " << get<2>(list_of_vehicle[i]) << " " << get<3>(list_of_vehicle[i])<< " " << get<4>(list_of_vehicle[i]) << endl;
   // }
   road=new char*[road_width];
   for(int i=0;i<road_width+2;i++){
      road[i]=new char[road_length];
      for(int j=0;j<road_length;j++){
        if(i==0||i==road_width+1)
           road[i][j]='-';
          else if(!road_signal&&j==50)
           road[i][j]='|';
          else
            road[i][j]=' ';
        } 
    }
    tuple<string,string,int> check;
    check = road_vehicle.pop_front();
    if(get<0>(check)=="start")
          start_simulation= true;            
    if(start_simulation){

            for(int i=0;i<Simulationtime && ;i++){
                check = road_vehicle.pop_front();
                if(get<0>(check)=="red")
                  road_signal=false;
                else if(get<0>(check)=="green")
                  road_signal=true;
                else if(get<0>(check)=="pass")
                {
                  if(get<2>(check)==0){

                  }
                  else{
                    road_vehicle.push_front(get<0>(check),get<0>(check),get<2>(check)-1);
                  }
                }
                else if(get<0>(check)=="end")
                {
                    if(road_empty()){
                      break;
                    }
                    road_vehicle.push_front(get<0>(check),get<0>(check),get<2>(check));
                }
                else{
                  int j;
                   for(j=0;j<vehicle_count;j++){
                      if(get<0>(list_of_vehicle[j])=get<0>(check))
                        automobiles.push_back(vehicle(get<0>(check),get<1>(check)));
                   }
                }

              cout<<"TIME ==>"<<i<<endl;
              make_frame();
              print_frame();
              }
      }
  return 0;
}
