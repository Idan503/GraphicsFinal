#pragma once

using namespace std;
#include<vector>

class TrainWagon
{
private:
	double red, green, blue;
	vector<double> position; // center in world coordinates
	vector<double> direction;
	double speed;
	bool head; // is this the head of the train

public:
	TrainWagon(double r, double g, double b, vector<double> position, vector<double> dir, double speed, bool head);
	void Draw();
	void Move();
	void SetSpeed(double s);
	bool IsHead();
	void DrawHeadWagon();
	void DrawWheel();
	void DrawHeadBase();
	void DrawHeadBody();
	void DrawRegularBase();
	void DrawRegularBody();
	void DrawRegularWagon();
	vector<double> GetPosition();
	vector<double> GetDirection();
};

