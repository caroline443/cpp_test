#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 50				//粒子个数
#define XMIN -100.0
#define XMAX 100.0
#define VMAX 20.0

const double w_max = 0.9;
const double w_min = 0.4;

class Particle {
	double* x;
	double y;
	double p;
	double* v;
	double* pbest;
	static double* gbest;
	double w;

public:
	Particle();
	~Particle();

	double getP();
	
	void refreshPbest(int i);
	void refreshGbest();
	void refreshW(int i);
};

class PSO {
	vector<Particle> swarm;
	double res;
	int n;						//迭代次数
public:
	PSO(int n);
	~PSO();

	double bestSolution();

	void refresh();		//更新gbest
};