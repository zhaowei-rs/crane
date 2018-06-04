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
	virtual void InitLayer() = 0;

	// load layer specific parameter from plain param file
	// return 0 if success
	virtual int LoadParam(FILE* fp_param);
	// load layer specific weight data from model file
	// return 0 if success
	virtual int LoadModel(FILE* fp_model_bin);

	virtual void ForwardLayer() = 0;
	virtual void BackwardLayer() = 0;

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

#endif // !CRANE_LAYER_H_