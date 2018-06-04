#include "blob.h"



Blob::Blob(const int num, const int channels, const int height, const int width)
	: capacity_(0)
{
	vector<int> shape(4);
	shape[0] = num;
	shape[1] = channels;
	shape[2] = height;
	shape[3] = width;

	Create(shape);

	return;
}

Blob::Blob(const vector<int>& shape) 
	: capacity_(0)
{
	Create(shape);
	return;
}

void Blob::Reshape(const int num, const int channels, const int height, const int width)
{
	vector<int> shape(4);
	shape[0] = num;
	shape[1] = channels;
	shape[2] = height;
	shape[3] = width;

	Create(shape);
	return;
}

void Blob::Create(const vector<int>& shape)
{
	size_ = 1;
	shape_.resize(shape.size());

	for (size_t i = 0; i < shape.size(); i++){
		size_ *= shape[i];
		shape_[i] = shape[i];
	}

	if (size_ > capacity_) {
		capacity_ = size_;
		data_.reset(new float(capacity_));
		diff_.reset(new float(capacity_));
	}
	return;
}


Blob::~Blob()
{
}
