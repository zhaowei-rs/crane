#ifndef CRANE_LAYER_H_
#define CRANE_LAYER_H_

#include "common.h"
#include "blob.h"

class Layer
{
public:
	Layer();
	virtual ~Layer();

	// init layer by specific parameters
	virtual void InitLayer();

	// load layer specific parameter from json param string
	// return 0 if success
	virtual int InitLayerByJson(string json_param);
	// load layer specific weight data from model file
	// return 0 if success
	virtual int LoadModel(FILE* fp_model_bin);

	virtual void ForwardLayer();
	virtual void BackwardLayer();

	// layer type name
	string type_;
	// layer name
	string name_;
	// learnable weights and bias of this layer
	vector<shared_ptr<Blob> > blobs_;
	// blob index which this layer needs as input
	vector<int> bottoms_;
	// blob index which this layer produces as output
	vector<int> tops_;
};

#define DEFINE_LAYER_CREATOR(name) \
    Layer* name##_layer_creator() { return new name; }

#endif // !CRANE_LAYER_H_