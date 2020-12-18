#include "pso.h"

//初始化
Particle::Particle() {
	x = new double[10];
	y = 0;
	v = new double[10];
	pbest = new double[10];
	w = 1.0;
	for (int i = 0; i < 10; i++) {
		x[i] = XMIN + rand() / (double)RAND_MAX * (XMAX - XMIN);
		v[i] = 0 + rand() / (double)RAND_MAX * (VMAX - 0);
		y += x[i] * x[i];
		pbest[i] = x[i];
	}
	p = y;
}
double* Particle::gbest = new double[10];
Particle::~Particle() {};

double Particle::getP() {
	return p;
}

void Particle::refreshPbest(int i) {
	y = 0;
	for (int i = 0; i < 10; i++) {
		double rand1 = rand() / (double)RAND_MAX * (1 - 0);
		double rand2 = rand() / (double)RAND_MAX * (1 - 0);
		refreshW(i);
		v[i] = w * v[i] + 0.5 * rand1 * (pbest[i] - x[i]) + 0.5 * rand2 * (gbest[i] - x[i]);
		if (v[i] > VMAX) {
			v[i] = VMAX;
		}
		if (v[i] < -1 * VMAX) {
			v[i] = -1 * VMAX;
		}
		x[i] = x[i] + v[i];
		y += x[i] * x[i];
	}
	if (p > y) {
		p = y;
		for (int i = 0; i < 10; i++) {
			pbest[i] = x[i];
		}
	}
}
void Particle::refreshGbest() {
	for (int i = 0; i < 10; i++) {
		gbest[i] = this->pbest[i];
	}
}
void Particle::refreshW(int i) {
	w = w_max - (w_max - w_min) * ((double)i / 20000);
}

PSO::PSO(int n) {
	this->n = n;
	Particle* p;
	for (int i = 0; i < N; i++) {
		p = new Particle;
		swarm.push_back(*p);
		if (i == 0) {
			res = swarm[i].getP();
			swarm[i].refreshGbest();
		}
		if (res > swarm[i].getP()) {
			res = swarm[i].getP();
			swarm[i].refreshGbest();
		}
	}
}

PSO::~PSO() {};

double PSO::bestSolution() {
	for (int i = 0; i < n; i++) {		//迭代次数
		refresh();
	}
	return res;
}

void PSO::refresh() {
	for (int i = 0; i < N; i++) {		//粒子个数
		swarm[i].refreshPbest(i);
		if (res > swarm[i].getP()) {
			res = swarm[i].getP();
			swarm[i].refreshGbest();
		}
	}
}