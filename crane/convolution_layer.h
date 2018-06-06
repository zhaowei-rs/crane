#ifndef CRANE_CONVOLUTION_LAYER_H_
#define CRANE_CONVOLUTION_LAYER_H_

#include "layer.h"

class Convolution : public Layer
{
public:
	Convolution();
	virtual ~Convolution();

	int InitLayerByJson(string json_param);
	int LoadModel(FILE* fp_model_bin);
	void ForwardLayer();
	void BackwardLayer();
};

#endif // !CRANE_CONVOLUTION_LAYER_H_

