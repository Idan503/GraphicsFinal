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

extern void DrawColorTire(int sides, double outer, double inner, vector<double> color, int step);
extern void DrawTexTire(int sides, double outer, double inner, int texture_id, bool replace, int step);

extern void DrawColorCube(vector<double> color);
extern void DrawTexCube(int texture_id, bool replace);

extern void DrawColorCylinder(vector<double> color, int sides);
extern void DrawColorCylinder(vector<double> color, int sides, double tr, double br);
extern void DrawTexCylinder(int sides, int texture_id, int num_rep, double top_radius, double bottom_radius, bool replace);

extern void DrawColorSphere(vector<double> color, int sides, int slices);
extern void DrawTexSphere(int sides, int slices, int texture_id, int num_rep, bool replace);

#endif


