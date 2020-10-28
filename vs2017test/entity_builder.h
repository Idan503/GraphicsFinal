#ifndef TRAIN
#define TRAIN

void DrawTrain();
void DrawBridge();
void DrawBridgeRoad();
void DrawBridgeArch();
double CalcBridgeCurveHeight(double x);
void DrawBridgeCurve();
void DrawBridgeInnerPoles();
void DrawBridgeSinglePole();
void MoveTrain();
void DrawBridgePoles(double);
void DrawTrees();
void InitTrain();
void InitSmoke();
void InitTrees();
void MoveSmoke();
void DrawSmoke();
void DrawWindowFilter();
void DrawSky();
void EmitSingleSmoke(int emit_index);
int GenerateTreeType(int i, int j);
void InitSmokeEmitTimer(int i);
bool IsCameraCloseToTrain();
void CheckAndPlayTrainSound(int i);

#endif


