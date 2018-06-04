#ifndef CRANE_NET_H
#define CRANE_NET_H

#include "common.h"
#include "blob.h"
#include "layer.h"

class Net
{
public:
	Net();
	~Net();

	vector<Blob> blobs;
	vector<Layer> layers;
};

#endif // !CRANE_NET_H