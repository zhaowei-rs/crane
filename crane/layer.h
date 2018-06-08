#ifndef CRANE_LAYER_H_
#define CRANE_LAYER_H_

#include "common.h"
#include "blob.h"

class Layer
{
public:
	Layer();
	virtual ~Layer();

	//// init layer by specific parameters
	//virtual void InitLayer();

	// load layer specific parameter from json param string
	// return 0 if success
	int InitLayerByJson(json11::Json json_param);
	// load layer specific weight data from model file
	// return 0 if success
	virtual int LoadModel(FILE* fp_model_bin);

	virtual void ForwardLayer()=0;
	virtual void BackwardLayer()=0;

	// layer type name
	string type_;
	// layer name
	string name_;

	// blob index which this layer needs as input
	vector<shared_ptr<Blob> > bottoms_;
	// blob index which this layer produces as output
	vector<shared_ptr<Blob> > tops_;
};

#define DEFINE_LAYER_CREATOR(name) \
    shared_ptr<Layer> name##_layer_creator() { return shared_ptr<Layer>(new name); }

#endif // !CRANE_LAYER_H_