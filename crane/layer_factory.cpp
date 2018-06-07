#include "layer_factory.h"
#include <map>
#include "convolution_layer.h"
#include "maxpool_layer.h"
#include "softmax_layer.h"

extern shared_ptr<Layer> Convolution_layer_creator();
extern shared_ptr<Layer> Maxpool_layer_creator();
extern shared_ptr<Layer> Softmax_layer_creator();

static map<string, LayerCreatorFunc> layer_registry = {
	{"convolution",  Convolution_layer_creator },
	{"maxpool", Maxpool_layer_creator },
	{"softmax", Softmax_layer_creator }
};

shared_ptr<Layer> CreateLayer(string type)
{
	LayerCreatorFunc layer_creator = layer_registry[type];
	if (!layer_creator)
	{
		fprintf(stderr, "layer type %d not enabled\n", type);//TODO: 
		return 0;
	}

	return layer_creator();
}

