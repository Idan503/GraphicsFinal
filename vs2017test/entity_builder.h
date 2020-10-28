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
void InitSmokeEmitTimer(int i);

#endif


