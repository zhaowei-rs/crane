#include "maxpool_layer.h"

DEFINE_LAYER_CREATOR(Maxpool)

Maxpool::Maxpool()
{

}

Maxpool::~Maxpool()
{

}

int Maxpool::InitLayerByJson(string json_param)
{
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
