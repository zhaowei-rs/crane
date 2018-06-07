#include <fstream>
#include "solver.h"

Solver::Solver(string solver_file, Phase phase)
{
	ifstream in_file(solver_file);
	string solver_str((istreambuf_iterator<char>(in_file)),istreambuf_iterator<char>());

	string err;
	const json11::Json json = json11::Json::parse(solver_str, err, json11::JsonParse::COMMENTS);

	phase_ = phase;
	device_ = json["device"].string_value();
	momentum_ = json["momentum"].number_value();
	learning_rate_ = json["learning_rate"].number_value();
	weight_decay_ = json["weight_decay"].number_value();

	weight_filler_ = json["weight_filler"].string_value();
	bias_filler_ = json["bias_filler"].string_value();

	json11::Json layers = json["layers"];
	net_.reset(new Net);
	net_->InitNetByJson(layers);
}

Solver::~Solver()
{
}

void Solver::TrainNetwork()
{
}
