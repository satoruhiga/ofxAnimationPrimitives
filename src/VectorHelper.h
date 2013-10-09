#pragma once

#include "ofMain.h"

template <typename T>
struct _$ : public vector<T>
{
	_$& operator,(const T& t)
	{
		this->push_back(t);
		return *this;
	}
};

#define $(type, ...) (_$<type>(), __VA_ARGS__)
#define $f(...) $(float, __VA_ARGS__)
#define $i(...) $(int, __VA_ARGS__)
#define $ui(...) $(unsigned int, __VA_ARGS__)
#define $v2(...) $(ofVec2f, __VA_ARGS__)
#define $v3(...) $(ofVec3f, __VA_ARGS__)
#define $v4(...) $(ofVec4f, __VA_ARGS__)
