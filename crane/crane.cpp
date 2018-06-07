#include <stdio.h>
#include "logger.h"
#include "solver.h"

int main()
{
	Solver test_solver("..\\examples\\vgg_16.json", Phase::TRAIN);


	getchar();
	return 0;
}