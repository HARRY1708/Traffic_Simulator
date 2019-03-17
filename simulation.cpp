#include <iostream>
#include <utility>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "Initializer.h"
#include <sstream>
#include <fstream>
#include <list>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>

using namespace std;
using namespace boost;

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
      if(automobiles[i].y2>road_length)
      automobiles.erase(automobiles.begin()+i);
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
            print_frame();
          }
              make_frame();
              T++;
              glutPostRedisplay();
              //}
      }
   
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(gray);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0,-rl*road_width/2);
        glVertex2f(-1.0,rl*road_width/2);
        glVertex2f(1.0,rl*road_width/2);
        glVertex2f(1.0,-rl*road_width/2);
    glEnd();
   for(int p=0;-rl*road_width/2+p*0.015+0.015<rl*road_width/2;p=p+4){
   glColor3f(white);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.01,-rl*road_width/2+p*0.015);
        glVertex2f(-0.01,-rl*road_width/2+p*0.015+0.015);
        glVertex2f(0.01,-rl*road_width/2+p*0.015+0.015);
        glVertex2f(0.01,-rl*road_width/2+p*0.015);
    glEnd();
   }
    // glColor3f(black);
    // glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    //  glBegin(GL_LINES);
    //     glVertex2f(-1.0+rl*road_signal_distance,-rl*road_width/2);
    //     glVertex2f(-1.0+rl*road_signal_distance,rl*road_width/2);
    // glEnd();

    glColor3f(yellow);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.075,.775);
        glVertex2f(0.075,0.625);
        glVertex2f(-0.075,0.625);
        glVertex2f(-0.075,0.775);
    glEnd();
if(road_signal)
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
     if(automobiles[i].color=="Yellow")
     glColor3f(yellow);
     else if(automobiles[i].color=="Blue")
     glColor3f(blue); 
     else if(automobiles[i].color=="Red")
      glColor3f(red);
     else if(automobiles[i].color=="Green")
      glColor3f(green);
     else if(automobiles[i].color=="White")
      glColor3f(white);
     else if(automobiles[i].color=="Black")
      glColor3f(black);
     else if(automobiles[i].color=="Silver")
     glColor3f(silver);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    // cout<<automobiles[i].x1*rw<<" "<<automobiles[i].x2*rw<<" "<<automobiles[i].y2*rl<<" "<<automobiles[i].y1*rl<<" "<<automobiles.size()<<endl;
    glBegin(GL_POLYGON);
        glVertex2f(-1.0+automobiles[i].y1*rl,automobiles[i].x1*rl-rl*road_width/2);
        glVertex2f(-1.0+automobiles[i].y2*rl,automobiles[i].x1*rl-rl*road_width/2);
        glVertex2f(-1.0+automobiles[i].y2*rl,automobiles[i].x2*rl-rl*road_width/2);
        glVertex2f(-1.0+automobiles[i].y1*rl,automobiles[i].x2*rl-rl*road_width/2);
        
    glEnd();
   }
    glFlush();
    glutSwapBuffers ();
}

int main(int argc, char** argv)
{   
    Initialize("config.ini");
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
    check = road_vehicle.front();
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