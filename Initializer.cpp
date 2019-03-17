#include <iostream>
#include <cstring>
#include <list>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <sstream>
#include <fstream>
#include "constants.h"
using namespace std;
using namespace boost;
void parseLine(const string &line)
{
  if (line[0] == '#' || line.empty())
    return;
  Tokenizer tokenizer(line, sep);
  vector<string> tokens;
  for (Tokenizer::iterator iter = tokenizer.begin(); iter != tokenizer.end(); iter++)
    tokens.push_back(*iter);
  //cout << tokens[0]<< endl;
  cout << tokens[0] <<endl;
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
    get<0>(temp)="start";
      get<1>(temp)="start";
      get<2>(temp)=0;
      road_vehicle.push_back(temp);
  }
  if(tokens[0]=="Signal")
  {
    if(tokens[1]=="RED"){
      get<0>(temp)="red";
      get<1>(temp)="red";
      get<2>(temp)=0;
      road_vehicle.push_back(temp);
    }
    else{
      get<0>(temp)="green";
      get<1>(temp)="green";
      get<2>(temp)=0;
      road_vehicle.push_back(temp); 
    }

  }
  for(int i=0;i<=vehicle_count;i++){
    if(tokens[0]==get<0>(list_of_vehicle[i]))
    {
      get<0>(temp)=tokens[0];
      get<1>(temp)=tokens[1];
      get<2>(temp)=1;
      road_vehicle.push_back(temp);
    }
  }
  if(tokens[0]=="Pass"){
    get<0>(temp)="pass";
    get<1>(temp)="pass";
    get<2>(temp)=stoi(tokens[1]);
    road_vehicle.push_back(temp);
  }
  if(tokens[0]=="END"){
     get<0>(temp)="end";
      get<1>(temp)="end";
      get<2>(temp)=0;
      road_vehicle.push_back(temp);
    end_bool=true;
  }

} 

void Initialize(string Filename){
  ifstream file;
     file.open(Filename);
 
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
     }
   file.close();
}