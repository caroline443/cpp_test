#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <math.h>

using namespace std;

const int numOfParticles = 50;
const int numOfIterations = 30000;
const int dimension = 10;
const double w_max = 0.9;
const double w_min = 0.4;
const double x_max = 30;
const double x_min = -1 * x_max;
const double v_max = x_max * 0.15;
const double c1 = 1;
const double c2 = 1;

double rand0_1();
double calcW(int i);
double calcFunction(double* x);


class Particle {
public:
	double* x;
	double* v;
	double* pbest;
	double fitness;
	double y;

	Particle();
	~Particle();
};

class PSO {
	vector<Particle> swarm;
	double* gbest;
	double bestSolution;
	double w;

public:
	PSO();
	~PSO();

	double solution();
	double updateGbest(int n);
	double updateParticle(Particle &particle, int n);
};