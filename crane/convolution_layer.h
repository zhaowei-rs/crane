#ifndef CRANE_CONVOLUTION_LAYER_H_
#define CRANE_CONVOLUTION_LAYER_H_

#include "layer.h"

class Convolution : public Layer
{
public:
	Convolution();
	virtual ~Convolution();

	int InitLayerByJson(json11::Json json_param);
	int LoadModel(FILE* fp_model_bin);
	void ForwardLayer();
	void BackwardLayer();

	int filters_;
	int	kernel_;
	int	stride_;
	int pad_;
	shared_ptr<Blob> weights_;
	shared_ptr<Blob> bias_;

	// blobs for batch norm
	bool is_batchnorm_;
	shared_ptr<Blob> mean_;
	shared_ptr<Blob> variance_;
	shared_ptr<Blob> scales_;
};

#endif // !CRANE_CONVOLUTION_LAYER_H_

