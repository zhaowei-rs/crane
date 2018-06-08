#ifndef CRANE_MAX_POOL_H_
#define CRANE_MAX_POOL_H_

#include "layer.h"

class Maxpool :public Layer
{
public:
	Maxpool();
	virtual ~Maxpool();

	int InitLayerByJson(json11::Json json_param);
	int LoadModel(FILE* fp_model_bin);
	void ForwardLayer();
	void BackwardLayer();

	int kernel_;
	int stride_;
	int pad_;
};

#endif // !CRANE_MAX_POOL_H_

