#include "convolution_layer.h"

DEFINE_LAYER_CREATOR(Convolution)

Convolution::Convolution()
{

}

Convolution::~Convolution()
{

}

int Convolution::InitLayerByJson(string json_param)
{
	return 0;
}

int Convolution::LoadModel(FILE * fp_model_bin)
{
	return 0;
}

void Convolution::ForwardLayer()
{
}

void Convolution::BackwardLayer()
{
}
