#ifndef CRANE_MAX_POOL_H_
#define CRANE_MAX_POOL_H_

#include "layer.h"

class Maxpool :public Layer
{
public:
	Maxpool();
	virtual ~Maxpool();

	int InitLayerByJson(string json_param);
	int LoadModel(FILE* fp_model_bin);
	void ForwardLayer();
	void BackwardLayer();
};

#endif // !CRANE_MAX_POOL_H_

