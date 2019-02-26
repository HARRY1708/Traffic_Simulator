#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
using namespace std;
char** road;
int road_length;
int road_width;
bool road_signal=false;
int default_maxspeed;
int default_acc;
int car_length=2;
int car_width=2;
int car_acc=1;
int car_maxspeed=1;
int bus_length=3;
int bus_width=2;
int bus_acc=1;
int bus_maxspeed=1;
int truck_length=4;
int truck_width=2;
int truck_acc=1;
int truck_maxspeed=1;
int bike_length=2;
int bike_width=1;
int bike_acc=1;
int bike_maxspeed=1;
int auto_length=2;
int auto_width=2;
int auto_acc=1;
int auto_maxspeed=1;
int Simulationtime=500;
class vehicle{	
 public :
  char type;
  int vehicle_length;
  int vehicle_width;
  int vehicle_speed;
  int vehicle_acc;
  string color;
  bool brake;
  int x1,y1,x2,y2;
  vehicle(char type,string color){
  	this->type=type;
  	this->color=color;
  	this->brake=false;
    if(type=='C'){
      this->vehicle_length=car_length;
      this->vehicle_width =car_width;
      this->vehicle_speed =car_maxspeed;
      this->vehicle_acc   =car_acc;
    }
    else if(type=='T'){
      this->vehicle_length=truck_length;
      this->vehicle_width =truck_width;
      this->vehicle_speed =truck_maxspeed;
      this->vehicle_acc   =truck_acc;
    }
    else if(type=='B'){
      this->vehicle_length=bus_length;
      this->vehicle_width =bus_width;
      this->vehicle_speed =bus_maxspeed;
      this->vehicle_acc   =bus_acc;
    }
    else if(type=='b'){
      this->vehicle_length=bike_length;
      this->vehicle_width =bike_width;
      this->vehicle_speed =bike_maxspeed;
      this->vehicle_acc   =bike_acc;
    }
    else if(type=='A'){
      this->vehicle_length=auto_length;
      this->vehicle_width =auto_width;
      this->vehicle_speed =auto_maxspeed;
      this->vehicle_acc   =auto_acc;
    }
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
    			road[j][k]=automobiles[i].type;
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
int main(){
    road_length=100;
    road_width=10;
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
    for(int i=0;i<Simulationtime;i++){
    	if(i%50==0)
    		road_signal=!road_signal;
    	if(i%4==0){
    		int x=abs(rand()%5);
            if(x==0)
            automobiles.push_back(vehicle('T',"Green"));
            else if(x==1)
            automobiles.push_back(vehicle('C',"Green"));
        	else if(x==2)
            automobiles.push_back(vehicle('B',"Green"));
        	else if(x==3)
            automobiles.push_back(vehicle('b',"Green"));
        	else 
            automobiles.push_back(vehicle('A',"Green"));
    	}
    cout<<"TIME ==>"<<i<<endl;
    make_frame();
    print_frame();
    }
	return 0;
}