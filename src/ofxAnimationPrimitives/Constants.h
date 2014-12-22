#pragma once

#include "ofMain.h"

#define OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE namespace ofx { namespace AnimationPrimitives {
#define OFX_ANIMATION_PRIMITIVES_END_NAMESPACE } }

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

#pragma mark - Vector Helper

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

#pragma mark - misc

namespace RTTI
{
	typedef void* TypeID;
	
	template <typename T>
	static TypeID getTypeID() {
		static size_t m = 0;
		return &m;
	}
};

template <typename T>
struct Ref_ : public ofPtr<T>
{
	Ref_() : ofPtr<T>() {}
	Ref_(T *t) : ofPtr<T>(t) {}
	Ref_(const ofPtr<T>& o) : ofPtr<T>(o) {}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE

namespace ofxAnimationPrimitives = ofx::AnimationPrimitives;

#ifdef _WIN32
#define isnormal(x) (_fpclass(x) == _FPCLASS_NN || _fpclass(x) == _FPCLASS_PN)
#define isinf(x) (!_finite(x))
#endif