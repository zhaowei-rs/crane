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
	void Create(const vector<int>& shape);

	inline string ShapeString() const {
		ostringstream stream;
		for (int i = 0; i < shape_.size(); ++i) {
			stream << shape_[i] << " ";
		}
		stream << "(" << size_ << ")";
		return stream.str();
	}
	inline const vector<int>& Shape() const { return shape_; }
	inline int NumAxes() const { return shape_.size(); }
	inline int Size() const { return size_; }
	inline int Size(int start_axis, int end_axis) const {
		int size = 1;
		for (int i = start_axis; i < end_axis; ++i) {
			size *= shape_[i];
		}
		return size;
	}
	inline int Size(int start_axis) const {
		return Size(start_axis, NumAxes());
	}

	inline int Num() const { return shape_[0]; }
	inline int Channels() const { return shape_[1]; }
	inline int Height() const { return shape_[2]; }
	inline int Width() const { return shape_[3]; }	

	inline int Offset(const int n, const int c = 0, const int h = 0, const int w = 0) const {
		return ((n * Channels() + c) * Height() + h) * Width() + w;
	}

	inline int offset(const vector<int>& indices) const {
		int offset = 0;
		for (int i = 0; i < NumAxes(); ++i) {
			offset *= shape_[i];
			if (indices.size() > i) {
				offset += indices[i];
			}
		}
		return offset;
	}

	// blob name
	string name_;
	// layer index which produce this blob as output
	int producer_;
	// layer index which need this blob as input
	vector<int> consumers_;

	// current total size of this blob
	size_t size_;
	// the max memory capacity of this blob
	size_t capacity_;
	// the lenghths of 4 dimension of this blob
	vector<int> shape_;
	// the data array of this blob
	shared_ptr<float> data_;
	// the gradient array of this blob
	shared_ptr<float> diff_;
};

#endif // !CRANE_BLOB_H_
