#include "convolution_layer.h"

DEFINE_LAYER_CREATOR(Convolution)

Convolution::Convolution()
{

}

Convolution::~Convolution()
{

}

int Convolution::InitLayerByJson(json11::Json json_param)
{
	Layer::InitLayerByJson(json_param);

	filters_ = json_param["filters"].int_value();
	kernel_ = json_param["kernel"].int_value();
	stride_ = json_param["stride"].int_value();
	pad_ = json_param["pad"].int_value();

	is_batchnorm_ = json_param["batch_norm"].bool_value();

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
