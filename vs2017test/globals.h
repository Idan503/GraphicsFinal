#ifndef GLOBALS    // To make sure you don't declare the function more than once by including the header multiple times.
#define GLOBALS

using namespace std;
#include <vector>

extern const double PI;

extern double current_time;

extern const int river_size;
extern const double bridge_height;

extern vector<vector<double>> ground;
extern const int ground_size;

extern const double train_speed;

extern vector<double> rail;
extern const double rail_width;

extern void DrawColorCylinder(vector<double> color, int sides);

#endif


