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
int car_length;
int car_width;
int car_acc;
int car_maxspeed;
int bus_length;
int bus_width;
int bus_acc;
int bus_maxspeed;
int truck_length;
int truck_width;
int truck_acc;
int truck_maxspeed;
int bike_length;
int bike_width;
int bike_acc;
int bike_maxspeed;
int auto_length;
int auto_width;
int auto_acc;
int auto_maxspeed;
int Simulationtime;
string current;
int vehicle_count=-1;
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
    while(get<0>(list_of_vehicle[xx])!=type)
          xx++;
    
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
// void make_frame(){
//    for(int i=0;i<road_width+2;i++){
//       for(int j=0;j<road_length;j++){
//         if(i==0||i==road_width+1)
//            road[i][j]='-';
//           else if(!road_signal&&j==50)
//            road[i][j]='|';
//           else
//             road[i][j]=' ';
//         } 
//     }
//     for(int i=0;i<automobiles.size();i++){
//       automobiles[i].update();
//       for(int j=automobiles[i].x1;j<=automobiles[i].x2;j++){
//         for(int k=max(automobiles[i].y2,0);k<=min(automobiles[i].y1,road_length-1);k++){
//           road[j][k]=automobiles[i].type;
//         }
//       }
//     }
// }
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
      current = tokens[3];
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
} 


int main(){
    
    ifstream file;
     file.open("config.ini");
 
    if (file.is_open())
       while(file.good())
       {
          char line[255];
          file.getline(line, 255);
          string linestring(line);
          parseLine(linestring);
       }
     else
     {
          cout << "Unable to open the file" << endl;
          return -2;
     }

  //   road_length=100;
  //   road_width=10;
  //   road=new char*[road_width];
  //  for(int i=0;i<road_width+2;i++){
  //     road[i]=new char[road_length];
  //     for(int j=0;j<road_length;j++){
  //       if(i==0||i==road_width+1)
  //          road[i][j]='-';
  //         else if(!road_signal&&j==50)
  //          road[i][j]='|';
  //         else
  //           road[i][j]=' ';
  //       } 
  //   }
  //   for(int i=0;i<Simulationtime;i++){
  //     if(i%50==0)
  //       road_signal=!road_signal;
  //     if(i%4==0){
  //       int x=abs(rand()%5);
  //           if(x==0)
  //           automobiles.push_back(vehicle("Truck","Green"));
  //           else if(x==1)
  //           automobiles.push_back(vehicle("Car","Green"));
  //         else if(x==2)
  //           automobiles.push_back(vehicle("Bus","Green"));
  //         else if(x==3)
  //           automobiles.push_back(vehicle("bike","Green"));
  //         // else 
  //         //   automobiles.push_back(vehicle("","Green"));
  //     }
  //   cout<<"TIME ==>"<<i<<endl;
  //   make_frame();
  //   print_frame();
  //   }
  // return 0;
}
