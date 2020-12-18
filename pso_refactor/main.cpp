#include "pso.h"

int main() {
	srand(time(0));
	PSO pso;
	cout << pso.solution() << endl;
	return 0;
}