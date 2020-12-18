#include "pso.h"

int main() {
	srand(time(0));
	PSO swarm(10000);
	cout << swarm.bestSolution() << endl;
}