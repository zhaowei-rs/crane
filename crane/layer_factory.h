#ifndef CRANE_LAYER_FACTORY_H
#define CRANE_LAYER_FACTORY_H

#include "layer.h"

// layer factory function
typedef shared_ptr<Layer>(*LayerCreatorFunc)();

// create layer from layer type
shared_ptr<Layer> CreateLayer(string type);

#endif // !CRANE_LAYER_FACTORY_H

