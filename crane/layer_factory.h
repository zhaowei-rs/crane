#ifndef CRANE_LAYER_FACTORY_H
#define CRANE_LAYER_FACTORY_H

#include "layer.h"

// layer factory function
typedef Layer* (*LayerCreatorFunc)();

// create layer from layer type
Layer* CreateLayer(string type);

#endif // !CRANE_LAYER_FACTORY_H

