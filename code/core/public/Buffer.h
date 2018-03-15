#ifndef GEMINI_Buffer_INCLUDE
#define GEMINI_Buffer_INCLUDE
#include "Common.h"

namespace gemini {
	
template <typename T>
class Buffer
{
	Buffer() = delete;
	Buffer(const Buffer&) = delete;
	Buffer& operator= (const Buffer&) = delete;
public:
	typedef T				value_type;
	typedef T&				reference;
	typedef const reference	const_reference;
	typedef std::size_t		size_type;
	typedef value_type*		pointer;
	typedef const pointer	const_pointer;

	Buffer(size_type size) : _pt(new value_type[size]), _size(size) { reset(); }
	~Buffer() { delete[] _pt; }

	void resize(size_type newSize, bool bKeep = true) {
		pointer ptr = new value_type[newSize];
		if (bKeep) {
			size_type n = newSize > _size ? _size : newSize;
			std::memcpy(ptr, _pt, n);
		}

		delete[] _pt;
		_pt = ptr;
		_size = newSize;
	}

	void reset()
	{ std::memset(_pt, 0, _size); }

	size_type size() const { return _size; }

	pointer begin() { return _pt; }
	const_pointer begin() const { return _pt; }
	pointer end() { return _pt + _size; }
	const_pointer end() const { return _pt + _size; }

	reference operator[] (size_type index) { return _pt[index]; }
	const_reference operator[] (size_type index) const { return _pt[index]; }
	
private:
	pointer   _pt;
	size_type _size;
};

}
#endif // GEMINI_Buffer_INCLUDE