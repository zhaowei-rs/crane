#include "maxpool_layer.h"

DEFINE_LAYER_CREATOR(Maxpool)

Maxpool::Maxpool()
{

}

Maxpool::~Maxpool()
{

}

int Maxpool::InitLayerByJson(json11::Json json_param)
{
	Layer::InitLayerByJson(json_param);

	kernel_ = json_param["kernel"].int_value();
	stride_ = json_param["stride"].int_value();
	pad_ = json_param["pad"].int_value();

	return 0;
}

int Maxpool::LoadModel(FILE * fp_model_bin)
{
	return 0;
}

void Maxpool::ForwardLayer()
{
}

void Maxpool::BackwardLayer()
{
}
