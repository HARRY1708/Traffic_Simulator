#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "constants.h"
#include <sstream>
#include <fstream>
#include <list>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>

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

void initial(string Filename){
  ifstream file;
     file.open(Filename);
    if (file.is_open()){
       while(!file.eof())
       {
          string line;
          getline(file,line);
          parseLine(line);
       }
    }
     else
     {
          cout << "Unable to open the file" << endl;
     }
   file.close();
}
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
  GLfloat X1,X2,Y1,Y2;
  vehicle(string type,string color){
    this->type=type;
    this->color=color;
    this->brake=false;
    int xx=0;
    while(get<0>(list_of_vehicle[xx])!=type){
      xx++;
    }
    this->vehicle_length = get<1>(list_of_vehicle[xx]);
    this->vehicle_width = get<2>(list_of_vehicle[xx]);
    this->vehicle_speed = get<3>(list_of_vehicle[xx]);
    this->vehicle_acc = get<4>(list_of_vehicle[xx]);

    this->x1=abs(rand()%(road_width-vehicle_width+1))+1;
    this->y1=-1;
    this->y2=-vehicle_length;
    this->x2=x1+vehicle_width-1;
    this->X1=x1;
    this->Y1=y1;
    this->Y2=y2;
    this->X2=x2;
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
  void updateint(){
    int cdist =closest_distance()-1;
    y1=y1+min(vehicle_speed,cdist);
    y2=y2+min(vehicle_speed,cdist);
  }

  void updatefloat(){
    int cdist =closest_distance()-1;
    Y1=Y1+min(vehicle_speed,cdist)*0.01;
    Y2=Y2+min(vehicle_speed,cdist)*0.01;
  }

};

vector<vehicle> automobiles;

void make_frame(){
  if(road_signal_distance==0)
     road_signal_distance=road_length/2;
   for(int i=0;i<road_width+2;i++){
      for(int j=0;j<road_length;j++){
        if(i==0||i==road_width+1)
           road[i][j]='-';
          else if(!road_signal&&j==road_signal_distance)
           road[i][j]='|';
          else
            road[i][j]=' ';
        } 
    }
    for(int i=0;i<automobiles.size();i++){
              automobiles[i].updateint();
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

void spinDisplay ()          // ORIGINAL FUNCTION
{  
    if(start_simulation && T<=Simulationtime*100){

            //for(int i=0;i<Simulationtime ;i++){
          if(T%100==0)
           {                
              check = road_vehicle.front();
               if(road_vehicle.size()!=0)
               road_vehicle.pop_front();
              cout << get<0>(check) << get<2>(check) << endl;
              if(get<0>(check)=="red")
                road_signal=false;
              else if(get<0>(check)=="green")
                road_signal=true;
              else if(get<0>(check)=="pass")
              {
                if(get<2>(check)==0){

                }
                else{
                  get<0>(check2)=get<0>(check);
                  get<1>(check2)=get<0>(check);
                  get<2>(check2)=get<2>(check)-1;
                  road_vehicle.push_front(check2);
                }
              }
              else if(get<0>(check)=="end")
              {
                  if(automobiles.size()==0){
                     start_simulation=false;
                     glutMainLoop();
                  }
                  road_vehicle.push_front(check);
              }
              else{
                 for(int j=0;j<vehicle_count;j++){
                    if(get<0>(list_of_vehicle[j])==get<0>(check))
                      automobiles.push_back(vehicle(get<0>(check),get<1>(check)));
                 }
              }

            cout<<"TIME ==>"<<T/100<<endl;
            make_frame();
            print_frame();
          }

          for(int i=0;i<automobiles.size();i++){
              automobiles[i].updatefloat();
             if(automobiles[i].Y2>road_length)
              automobiles.erase(automobiles.begin()+i);
          }
          
          T++;
          glutPostRedisplay();
      }
   
}

void display()
{   float rl=(2.00)/road_length;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(gray);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0,-rl*road_width);
        glVertex2f(-1.0,rl*road_width);
        glVertex2f(1.0,rl*road_width);
        glVertex2f(1.0,-rl*road_width);
    glEnd();
   for(int p=0;-rl*road_width+p*0.015+0.015<rl*road_width;p=p+4){
   glColor3f(white);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.01,-rl*road_width+p*0.015);
        glVertex2f(-0.01,-rl*road_width+p*0.015+0.015);
        glVertex2f(0.01,-rl*road_width+p*0.015+0.015);
        glVertex2f(0.01,-rl*road_width+p*0.015);
    glEnd();
   }
    glColor3f(yellow);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.075,.775);
        glVertex2f(0.075,0.625);
        glVertex2f(-0.075,0.625);
        glVertex2f(-0.075,0.775);
    glEnd();
if(!road_signal)
    glColor3f(red);
 else
   glColor3f(green);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.05,.75);
        glVertex2f(0.05,0.65);
        glVertex2f(-0.05,0.65);
        glVertex2f(-0.05,0.75);
    glEnd();

  for(int i=0;i<automobiles.size();i++){ 
     if(automobiles[i].color=="YELLOW")
     glColor3f(yellow);
     else if(automobiles[i].color=="BLUE")
     glColor3f(blue); 
     else if(automobiles[i].color=="RED")
      glColor3f(red);
     else if(automobiles[i].color=="GREEN")
      glColor3f(green);
     else if(automobiles[i].color=="WHITE")
      glColor3f(white);
     else if(automobiles[i].color=="BLACK")
      glColor3f(black);
     else if(automobiles[i].color=="SILVER")
     glColor3f(silver);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    // cout<<automobiles[i].x1*rw<<" "<<automobiles[i].x2*rw<<" "<<automobiles[i].y2*rl<<" "<<automobiles[i].y1*rl<<" "<<automobiles.size()<<endl;
    glBegin(GL_POLYGON);
        glVertex2f(-1.0+automobiles[i].y1*rl,2*automobiles[i].x1*rl-rl*road_width);
        glVertex2f(-1.0+automobiles[i].y2*rl,2*automobiles[i].x1*rl-rl*road_width);
        glVertex2f(-1.0+automobiles[i].y2*rl,2*automobiles[i].x2*rl-rl*road_width);
        glVertex2f(-1.0+automobiles[i].y1*rl,2*automobiles[i].x2*rl-rl*road_width);
        
    glEnd();
   }
    glFlush();
    glutSwapBuffers ();
}

int main(int argc, char** argv)
{ 
  initial("config.ini");
   if(road_signal_distance==0)
     road_signal_distance=road_length/2;
   cout<<road_signal_distance<<" "<<road_signal<<endl;
  road=new char*[road_width+2];
   for(int i=0;i<road_width+2;i++){
        road[i]=new char[road_length];
        for(int j=0;j<road_length;j++){
        if(i==0||i==road_width+1)
           road[i][j]='-';
          else if(!road_signal&&j==road_signal_distance)
           road[i][j]='|';
          else
            road[i][j]=' ';
        } 
    }
   
    check = road_vehicle.front();
    if(road_vehicle.size()!=0)
      road_vehicle.pop_front();
    if(get<0>(check)=="start")
       start_simulation = true; 
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(10000,10000);
    glutInitWindowPosition(100,100);
    glutCreateWindow("TRAFFIC_SIMULATOR");
    glutDisplayFunc(display);
    glutIdleFunc (spinDisplay);
    glutMainLoop();
}
