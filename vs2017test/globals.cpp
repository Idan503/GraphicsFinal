#include "globals.h"


// Global variables that will be used in various files in the project

const double PI = 3.1415;
const int ground_size = 100;
double current_time = 0;
const int river_size = 10;
int current_texture_id = -1;
extern vector<vector<double> > ground(ground_size,vector<double>(ground_size,0));