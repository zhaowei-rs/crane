#include "net.h"
#include "layer_factory.h"

Net::Net()
{
}

Net::~Net()
{
}

int Net::InitNetByJson(json11::Json net_param)
{
	json11::Json::array layers_params = net_param.array_items();

	for (size_t i = 0; i < layers_params.size(); i++){
		json11::Json layer_param = layers_params[i];
		layers_.push_back(CreateLayer(layer_param["type"].string_value()));
		layers_[layers_.size() - 1]->InitLayerByJson(layer_param);

		json11::Json::array bottoms = layer_param["bottoms"].array_items();
		json11::Json::array tops = layer_param["tops"].array_items();

		for (auto name : bottoms){
			layers_[layers_.size() - 1]->bottoms_.push_back(blobs_[name.string_value()]);
		}

		for (auto name : tops){
			blobs_[name.string_value()] = shared_ptr<Blob>(new Blob);
			layers_[layers_.size() - 1]->tops_.push_back(blobs_[name.string_value()]);
		}
	}



	return 0;
}

const vector<Blob*> Net::Forward(float *loss)
{
	vector<Blob*> a;
	return a;
}

void Net::Backward()
{

}

void Net::Update()
{

}