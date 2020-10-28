#include "SmokeParticle.h"
using namespace std;
#include<vector>
#include "glut.h"
#include "globals.h"



SmokeParticle::SmokeParticle(vector<double> dir, double start_speed, double end_speed,
							double start_size, double end_size, int life_time)
{
	this->color = vector<double>{ 0.2,0.2,0.25, 1};
	this->position = vector<double>{0,0,0}; //pos init in Emit()
	this->direction = dir;
	this->start_speed = start_speed;
	this->end_speed = end_speed;
	this->life_total = life_time;
	this->life_remaining = life_time;
	this->start_size = start_size;
	this->end_size = end_size;
	this->active = false;
}

void SmokeParticle::Draw()
{
	if (!active)
		return;

	double current_alpha = (double)life_remaining /life_total; //linear alpha change
	color[3] = (double)fmax(0,current_alpha - 0.35);


	double current_size = start_size + ((end_size - start_size) * (1.0 -(double)life_remaining/life_total));

	glPushMatrix();
	glTranslated(position[0], position[1], position[2]);
	glScaled(current_size, current_size + 0.5*(1-current_alpha), current_size); //oval shape over time
	DrawColor4dSphere(color, 16, 64);

	glPopMatrix();

}

void SmokeParticle::Move()
{
	double current_speed = start_speed + ((end_speed - start_speed) * (1.0 - (double)life_remaining / life_total));

	if (active) {
		int i;
		for (i = 0; i < 3; i++)
		{
			position[i] += direction[i] * current_speed;

			// updating position of particle
		}
		life_remaining--;
	}

	if (life_remaining <= 0)
		active = false;

}

double GetRandNum(double strength)
{
	return 1 + (double)((rand() % 100 - 50.0) * strength) / 1000.0;
}

void SmokeParticle::RandomizeAttrs(double strength)
{
	
	this->start_speed *= GetRandNum(strength);

	this->end_speed *= GetRandNum(strength);

	this->start_size *= GetRandNum(strength);

	this->end_size *= GetRandNum(strength);

	this->direction[0] *= GetRandNum(strength);
	this->direction[1] *= GetRandNum(strength);
}



void SmokeParticle::SetSpeed(double start, double end)
{
	this->start_speed = start;
	this->end_speed = end;
}


void SmokeParticle::Emit(vector<double> origin)
{
	int i;
	for (i = 0; i < 3; i++)
	{
		position[i] = origin[i];

		// Setting init pos
	}

	life_remaining = life_total;
	active = true;
}

vector<double> SmokeParticle::GetPosition()
{
	return this->position;
}

vector<double> SmokeParticle::GetDirection()
{
	return this->direction;
}
