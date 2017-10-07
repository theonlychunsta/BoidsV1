#include "Flock.h"

Flock::Flock()
{
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;
}


Flock::~Flock()
{
}

void Flock::updateFlock()
{
	std::vector<std::thread> boidThreads;

	for (int i = 0; i < boids.size(); i++) {
		boidThreads.push_back(std::thread(&Boid::updatePosition, &boids[i], &boids, i));
	}

	for (int i = 0; i < boids.size(); i++) {
		boidThreads[i].join();
	}

}