#include "layer.h"

Layer::Layer()
{
}


Layer::~Layer()
{
}

int Layer::InitLayerByJson(json11::Json json_param)
{
	type_ = json_param["type"].string_value();
	name_ = json_param["name"].string_value();
	return 0;
}

int Layer::LoadModel(FILE* /*fp_model_bin*/)
{
	return 0;
}