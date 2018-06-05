#include "layer_factory.h"
#include <map>
#include "convolution_layer.h"
#include "maxpool_layer.h"
#include "softmax_layer.h"

extern Layer* Convolution_layer_creator();
extern Layer* Maxpool_layer_creator();
extern Layer* Softmax_layer_creator();

static map<string, LayerCreatorFunc> layer_registry = {
	{"Convolution",  Convolution_layer_creator },
	{"Maxpool", Maxpool_layer_creator },
	{"Softmax", Softmax_layer_creator }
};

Layer* CreateLayer(string type)
{
	LayerCreatorFunc layer_creator = layer_registry[type];
	if (!layer_creator)
	{
		fprintf(stderr, "layer type %d not enabled\n", type);
		return 0;
	}

	return layer_creator();
}

