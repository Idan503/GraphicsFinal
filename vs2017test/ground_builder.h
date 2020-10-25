#ifndef GROUND // To make sure you don't declare the function more than once by including the header multiple times.
#define GROUND

void DrawGround();
void BuildGroundTerrain();
void DrawWater();
void BuildRiverPath();
void BuildSeismologic();
void BuildRandomWalk();
void BuildFlatGround();
bool ValidateGroundBuild();
void SmoothTerrain();
void SetHeightMaterial(int h, int i, int j);
bool IsNearSnow(int i, int j);
void PrepareRailRoad();
void DrawRail();
void InitTrain();
double GetMaxBridgeGroundHeight();
#endif


