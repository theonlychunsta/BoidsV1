#include "Flock.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <thread>


std::vector<Flock>flockList;


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(50 / 256.0f, 150 / 256.0f, 200 / 256.0f, 1);

	for (int i = 0; i < flockList.size(); i++)
	{
		for (int j = 0; j < flockList[i].boids.size(); j++)
		{
			glColor3b(flockList[i].r, flockList[i].g, flockList[i].b);
			glBegin(GL_TRIANGLES);
			glVertex2f(flockList[i].boids[j].Coordinate.X, flockList[i].boids[j].Coordinate.Y + 0.01);
			glVertex2f(flockList[i].boids[j].Coordinate.X - 0.005, flockList[i].boids[j].Coordinate.Y - 0.005);
			glVertex2f(flockList[i].boids[j].Coordinate.X + 0.005, flockList[i].boids[j].Coordinate.Y - 0.005);
			glEnd();
		}

	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void updateFlocks()
{
	std::vector<std::thread> flockThreads;

	for (int i = 0; i < flockList.size(); i++) {
		flockThreads.push_back(std::thread(&Flock::updateFlock, &flockList[i]));
	}

	for (int i = 0; i < flockList.size(); i++){
		flockThreads[i].join();
	}
}

int main(int ptr, char** charptr)
{
	glutInit(&ptr, charptr);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(555, 555);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("May God Have Mercy On Us, FML, FML, FML, FML, FML");
	glutDisplayFunc(draw);

	srand((time(0)));


	int numberOfFlocks = 5;
	int numberOfBoids = 5;


	// GENERATE THE FLOCKS AND THE BOIDS.
	for (int i = 0; i < numberOfFlocks; i++) {
		Flock f;
		for (int x = 0; x < numberOfBoids; x++) {
			f.boids.push_back(Boid());
		}
		flockList.push_back(f);
	}

	int timeToDrawGraphics = 0;
	int timeToUpdate = 0;

	while (true)
	{
		auto currentTime = GetTickCount();

		if (currentTime >= timeToDrawGraphics) {
			glutMainLoopEvent();
			timeToDrawGraphics = currentTime + 16;
		}

		if (currentTime >= timeToUpdate) {
			updateFlocks();
			timeToUpdate = currentTime + 33;
		}
	}
}
