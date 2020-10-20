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
	TrainWagon(double r, double g, double b, vector<double> position, vector<double> dir, double speed);
	void Draw();
	void Move();
	void SetSpeed(double s);
	bool IsHead();
	vector<double> GetPosition();
	vector<double> GetDirection();
};

