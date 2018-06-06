#ifndef CRANE_SOFTMAX_LAYER_H_
#define CRANE_SOFTMAX_LAYER_H_

#include "layer.h"

class Softmax : public Layer
{
public:
	Softmax();
	virtual ~Softmax();

	int InitLayerByJson(string json_param);
	int LoadModel(FILE* fp_model_bin);
	void ForwardLayer();
	void BackwardLayer();
};

#endif // !CRANE_SOFTMAX_LAYER_H_

