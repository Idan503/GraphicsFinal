#pragma once
#ifndef BRIDGE
#define BRIDGE



	void DrawBridgeArch();
	void DrawBridgeRoad();
	void DrawBridgePoles(double thinkness);
	void DrawBridgeSinglePole();
	void DrawBridgeCurve();
	double CalcBridgeCurveHeight(double x);
	void DrawBridgeInnerPoles();

#endif
