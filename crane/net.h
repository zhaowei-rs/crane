#ifndef CRANE_NET_H_
#define CRANE_NET_H_

#include "common.h"
#include "blob.h"
#include "layer.h"

class Net
{
public:
	Net();
	~Net();

	int InitNetByJson(json11::Json net_param);

	const vector<Blob*> Forward(float *loss = NULL);

	void Backward();

	void Update();

	string name_;
	vector<shared_ptr<Blob> > blobs_;
	vector<shared_ptr<Layer> > layers_;
};

#endif // !CRANE_NET_H_