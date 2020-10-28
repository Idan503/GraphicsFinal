#pragma once
using namespace std;
#include<vector>

class SmokeParticle
{

private:
	vector<double> color; //4d vector (with alpha)
	vector<double> position; // center in world coordinates
	vector<double> direction;
	int life_total; // in frames
	int life_remaining;
	double start_size;
	double end_size;
	double start_speed;
	double end_speed;
	bool active;

public:
	SmokeParticle(vector<double> dir, double start_speed, double end_speed, double start_size, double end_size, int life_time);
	void Draw();
	void Move();
	void RandomizeAttrs(double strength);
	void SetSpeed(double start, double end);
	void Emit(vector<double> origin);
	vector<double> GetPosition();
	vector<double> GetDirection();
};

