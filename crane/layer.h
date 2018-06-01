#ifndef CRANE_LAYER_H_
#define CRANE_LAYER_H_

#include "common.h"
#include "blob.h"

class Layer
{
public:
	Layer();
	virtual ~Layer();



	vector<Blob> blobs_;
};

#endif // !CRANE_LAYER_H_