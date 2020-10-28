#ifndef GLOBALS    // To make sure you don't declare the function more than once by including the header multiple times.
#define GLOBALS

using namespace std;
#include <vector>

extern const double PI;
extern const double E;

extern double current_time;

extern int selected_view;
// 0 = regular view, 1 = side view, 2 = train driver view, 3 = window view

extern const int river_size;
extern const double bridge_height;

extern const double snow_height;

extern double eyex, eyey, eyez; //camera position

extern vector<vector<double>> ground;
extern const int ground_size;

extern const double train_speed;
extern vector<double> train_head_position;
extern vector<double> train_window_position;
extern const vector<double> train_window_color;

extern vector<double> rail;
extern const double rail_width;

extern void DrawColorTire(int sides, double outer, double inner, vector<double> color, int step);
extern void DrawTexTire(int sides, double outer, double inner, int texture_id, bool replace, int step);

extern void DrawColorCube(vector<double> color);
extern void DrawTexCube(int texture_id, int num_rep, bool replace = true);

extern void DrawColorCylinder(vector<double> color, int sides);
extern void DrawColorCylinder(vector<double> color, int sides, double tr, double br);
extern void DrawColor4dCylinder(vector<double> color, int sides, double tr, double br);
extern void DrawTexCylinder(int sides, int texture_id, int num_rep, bool replace = true);
extern void DrawTexCylinder(int sides, int texture_id, int num_rep, double top_radius, double bottom_radius, bool replace = true);
extern void DrawTexCylinder2(int n, int tnum, int num_repeat, double tr, double br, double tpart, double bpart, bool replace = true);

extern void DrawColorSphere(vector<double> color, int sides, int slices);
extern void DrawColor4dSphere(vector<double> color, int sides, int slices);
extern void DrawTexSphere(int sides, int slices, int texutre_id, int num_rep, int vert_rep, bool replace = true);

#endif


