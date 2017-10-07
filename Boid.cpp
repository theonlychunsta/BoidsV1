#include "Flock.h"


Boid::Boid()
{
	Coordinate.X = (float)rand() / RAND_MAX;
	Coordinate.Y = (float)rand() / RAND_MAX;
}


Boid::~Boid()
{
}

void Boid::updatePosition(std::vector<Boid>* m, int boidIndex)
{
	Position total, distance, velocity;

	total = centerOfMass(*m, boidIndex);
	distance = distanceAway(*m, boidIndex);
	velocity = matchVelocity(*m, boidIndex);

	m->at(boidIndex).Velocity.X += total.X + distance.X + velocity.X;
	m->at(boidIndex).Velocity.Y += total.Y + distance.Y + velocity.Y;

	//LIMIT POSITION OF BOIDS.
	if (m->at(boidIndex).Coordinate.X >= 1.0f) {
		m->at(boidIndex).Velocity.X = -0.01f;
	}
	if (m->at(boidIndex).Coordinate.X <= -1.0f){
		m->at(boidIndex).Velocity.X = 0.01f;
	}
	if (m->at(boidIndex).Coordinate.Y >= 1.0f) {
		m->at(boidIndex).Velocity.Y = -0.01f;
	}
	if (m->at(boidIndex).Coordinate.Y <= -1.0f) {
		m->at(boidIndex).Velocity.Y = 0.01f;
	}

	limitVelocity(m->at(boidIndex));

	m->at(boidIndex).Coordinate.X += m->at(boidIndex).Velocity.X;
	m->at(boidIndex).Coordinate.Y += m->at(boidIndex).Velocity.Y;

}

Position Boid::centerOfMass(std::vector<Boid> m, int boidIndex)
{
	Position total;

	for (int i = 0; i < m.size(); i++)
	{
		if (i != boidIndex)
		{
			total.X += m[i].Coordinate.X;
			total.Y += m[i].Coordinate.Y;
		}
	}

	total.X = total.X / (m.size() - 1);
	total.Y = total.Y / (m.size() - 1);

	total.X = (total.X - m[boidIndex].Coordinate.X) / 100;
	total.Y = (total.Y - m[boidIndex].Coordinate.Y) / 100;

	return total;
}

Position Boid::distanceAway(std::vector<Boid> m, int boidIndex)
{
	Position distance;

	for (int i = 0; i < m.size(); i++)
	{
		if (i != boidIndex) {
			float someVelocityX = m[i].Coordinate.X - m[boidIndex].Coordinate.X;
			float someVelocityY = m[i].Coordinate.Y - m[boidIndex].Coordinate.Y;

			if (sqrt(someVelocityX * someVelocityX + someVelocityY * someVelocityY) < 0.01)
			{
				distance.X = distance.X - (m[i].Coordinate.X - m[boidIndex].Coordinate.X);
				distance.Y = distance.Y - (m[i].Coordinate.Y - m[boidIndex].Coordinate.Y);
			}
		}
	}
	
	return distance;
}

Position Boid::matchVelocity(std::vector<Boid> m, int boidIndex)
{
	Position velocity;

	for (int i = 0; i < m.size(); i++)
	{
		if (i != boidIndex)
		{
			velocity.X += m[i].Velocity.X;
			velocity.Y += m[i].Velocity.Y;
		}

	}

	velocity.X /= (m.size() - 1);
	velocity.Y /= (m.size() - 1);

	velocity.X = (velocity.X - m[boidIndex].Velocity.X) / 8;
	velocity.Y = (velocity.Y - m[boidIndex].Velocity.Y) / 8;

	return velocity;
}

Position Boid::limitVelocity(Boid& m)
{
	Position limitedVelocity;
	float vLimit = 0.01;
	float norm = sqrt(m.Velocity.X*m.Velocity.X + m.Velocity.Y*m.Velocity.Y);

	if (norm > vLimit)
	{
		limitedVelocity.X = m.Velocity.X / norm * vLimit;
		limitedVelocity.Y = m.Velocity.Y / norm * vLimit;
	}

	return limitedVelocity;
}

