#include <iostream>
#include <cstring>
#include <list>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>
using namespace std;
using namespace boost;
#define blue 0.0,0.0,1.0
#define green 0.0,1.0,.0
#define red 1.0,0.0,0.0
#define yellow 1.0,1.0,0.0
#define black 0.0,0.0,0.0 
#define white 1.0,1.0,1.0
#define gray 0.6,0.6,0.6
#define silver 0.75,0.75,0.75
typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;
static const char_separator<char> sep(" ","#");  
int T =0;
char** road;
int Road_Id;
int road_length=100;
int road_width=20;
int road_signal_distance=0;
bool road_signal=false;
int default_maxspeed;
int default_acc;
int Simulationtime=500;
bool start_simulation;
bool end_bool;
string current;
int vehicle_count=-1;
tuple <string,string,int> temp;
list <tuple< string , string ,int > > road_vehicle;   //vehicle type,colour,to_wait_for
tuple <string,int,int,int,int,string> list_of_vehicle[10]; //tuple of <name,length,width,speed,acc,colour>
tuple<string,string,int> check2;
    tuple<string,string,int> check;
