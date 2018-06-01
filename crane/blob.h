#ifndef CRANE_BLOB_H_
#define	CRANE_BLOB_H_

#include "common.h"

class Blob
{
public:
	Blob() : data_(NULL), diff_(NULL), size_(0), capacity_(0){};
	
	explicit Blob(const int num, const int channels, const int height, const int width);
	explicit Blob(const vector<int>& shape);

	virtual ~Blob();

	void Reshape(const int num, const int channels, const int height, const int width);
	void Reshape(const vector<int>& shape);

	inline string shape_string() const {
		ostringstream stream;
		for (int i = 0; i < shape_.size(); ++i) {
			stream << shape_[i] << " ";
		}
		stream << "(" << size_ << ")";
		return stream.str();
	}
	inline const vector<int>& shape() const { return shape_; }
	inline int num_axes() const { return shape_.size(); }
	inline int size() const { return size_; }
	inline int size(int start_axis, int end_axis) const {
		int size = 1;
		for (int i = start_axis; i < end_axis; ++i) {
			size *= shape_[i];
		}
		return size;
	}
	inline int size(int start_axis) const {
		return size(start_axis, num_axes());
	}

	inline int num() const { return shape_[0]; }
	inline int channels() const { return shape_[1]; }
	inline int height() const { return shape_[2]; }
	inline int width() const { return shape_[3]; }	

	inline int offset(const int n, const int c = 0, const int h = 0, const int w = 0) const {
		return ((n * channels() + c) * height() + h) * width() + w;
	}

	inline int offset(const vector<int>& indices) const {
		int offset = 0;
		for (int i = 0; i < num_axes(); ++i) {
			offset *= shape_[i];
			if (indices.size() > i) {
				offset += indices[i];
			}
		}
		return offset;
	}

protected:
	size_t size_;
	size_t capacity_;
	vector<int> shape_;
	shared_ptr<float> data_;
	shared_ptr<float> diff_;
};

#endif // !CRANE_BLOB_H_
