#pragma once
#include "Position.h"

class Boid
{
public:
	Boid();
	~Boid();
	Position Velocity;
	Position Coordinate;

	void updatePosition(std::vector<Boid>* m, int boidIndex);
	Position centerOfMass(std::vector<Boid> m, int vectorIndex);
	Position distanceAway(std::vector<Boid>m, int vectorIndex);
	Position matchVelocity(std::vector<Boid>m, int vectorIndex);
	Position limitVelocity(Boid& m);

};

