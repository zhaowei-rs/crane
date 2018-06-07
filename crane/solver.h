#ifndef CRANE_SOLVER_H_
#define CRANE_SOLVER_H_

#include "common.h"
#include "net.h"

enum Phase {
	TRAIN = 0,
	TEST = 1
};

class Solver
{
public:
	Solver(string solver_file, Phase phase);
	~Solver();

	void TrainNetwork();

	Phase phase_;
	string device_;
	int batch_;
	int channel_;
	int height_;
	int width_;

	float momentum_;
	float learning_rate_;
	float weight_decay_;
	string weight_filler_;
	string bias_filler_;

	shared_ptr<Net> net_;
};

#endif // !CRANE_SOLVER_H_
