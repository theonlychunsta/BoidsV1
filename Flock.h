#pragma once
#include<vector>
#include<thread>
#include "Boid.h"

class Flock
{
public:
	Flock();
	~Flock();

	std::vector<Boid>boids;
	int r, g, b;

	void updateFlock();

};

