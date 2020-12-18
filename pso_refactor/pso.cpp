#include "pso.h"

double rand0_1() {
	return rand() / (double)RAND_MAX;
}
double calcW(int i) {
	return (w_max - w_min) * ((double)numOfIterations - i) / numOfIterations + w_min;
}
double calcFunction(double *x) {
	double y1 = 0, y2 = 0;
	/*for (int i = 0; i < dimension; i++) {
		y += x[i] * x[i];
	}*/
	/*for (int i = 0; i < dimension; i++) {
		y1 += abs(x[i]);
		y2 *= abs(x[i]);
	}
	y1 += y2;*/
	/*for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < i; j++) {
			y2 += x[i];
		}
		y1 += y2 * y2;
	}*/
	/*double max = -100;
	for (int i = 0; i < dimension; i++) {
		if (max < abs(x[i])) {
			max = abs(x[i]);
		}
	}
	y1 = max;*/
	for (int i = 0; i < dimension - 1; i++) {
		y1 += 100 * pow((x[i + 1] - x[i] * x[i]), 2) + pow((x[i] - 1), 2);
	}
	/*for (int i = 0; i < dimension; i++) {
		y1 += pow(x[i] + 0.5, 2);
	}*/
	/*for (int i = 0; i < dimension; i++) {
		y1 += i * pow(x[i], 4);
	}
	y1 += rand0_1();*/
	/*for (int i = 0; i < dimension; i++) {
		y1 += -1 * x[i] * sin(sqrt(abs(x[i])));
	}*/
	/*for (int i = 0; i < dimension; i++) {
		y1 += pow(x[i], 2) - 10 * cos(2 * 3.1415926 * x[i]) + 10;
	}*/
	return y1;
}

Particle::Particle() {
	x = new double[dimension];
	v = new double[dimension];
	pbest = new double[dimension];
	for (int i = 0; i < dimension; i++) {
		x[i] = (x_max - x_min) * rand0_1() - (x_max - x_min) / 2;
		v[i] = v_max * 2.0 * rand0_1() - v_max;
		pbest[i] = x[i];
	}
	y = calcFunction(x);
	fitness = y;
}
Particle::~Particle() {
	
}

PSO::PSO() {
	Particle *particle;
	gbest = new double[dimension];
	int j;
	for (int i = 0; i < numOfParticles; i++) {
		particle = new Particle;
		swarm.push_back(*particle);
		if (i == 0) {
			j = i;
			bestSolution = swarm[i].fitness;
		}
		else {
			if (bestSolution > swarm[i].fitness) {
				j = i;
				bestSolution = swarm[i].fitness;
			}
		}
	}
	for (int i = 0; i < dimension; i++) {
		gbest[i] = swarm[j].pbest[i];
	}
}
PSO::~PSO() {

}

double PSO::solution() {
	for (int i = 0; i < numOfIterations; i++) {
		updateGbest(i);
	}
	return bestSolution;
}

double PSO::updateGbest(int n) {
	for (int i = 0; i < numOfParticles; i++) {
		updateParticle(swarm[i], n);
		if (bestSolution > swarm[i].fitness) {
			bestSolution = swarm[i].fitness;
			for (int j = 0; j < dimension; j++) {
				gbest[j] = swarm[i].pbest[j];
			}
		}
	}
	return bestSolution;
}
double PSO::updateParticle(Particle &particle, int n) {
	w = calcW(n);
	for (int i = 0; i < dimension; i++) {
		particle.v[i] = particle.v[i] * w + c1 * rand0_1() * (particle.pbest[i] - particle.x[i]) + c2 * rand0_1() * (gbest[i] - particle.x[i]);
		if (particle.v[i] > v_max) {
			particle.v[i] = v_max;
		}
		else if (particle.v[i] < -1 * v_max) {
			particle.v[i] = -1 * v_max;
		}
		particle.x[i] += particle.v[i];
	}
	particle.y = calcFunction(particle.x);
	if (particle.fitness > particle.y) {
		particle.fitness = particle.y;
		for (int i = 0; i < dimension; i++) {
			particle.pbest[i] = particle.x[i];
		}
	}
	return particle.fitness;
}