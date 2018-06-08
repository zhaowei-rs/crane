#include "softmax_layer.h"

DEFINE_LAYER_CREATOR(Softmax)

Softmax::Softmax()
{

}

Softmax::~Softmax()
{

}

int Softmax::InitLayerByJson(json11::Json json_param)
{
	Layer::InitLayerByJson(json_param);
	return 0;
}

int Softmax::LoadModel(FILE * fp_model_bin)
{
	return 0;
}

void Softmax::ForwardLayer()
{
}

void Softmax::BackwardLayer()
{
}
