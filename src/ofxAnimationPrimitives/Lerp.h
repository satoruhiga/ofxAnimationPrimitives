#pragma once

#include "Timer.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

template <typename T>
class Lerp : public Ticker
{
public:
	
	Lerp() : value(0), target(0), speed(0.05) { play(); }
	Lerp(const T& v) : value(v), target(v), speed(0.05) { play(); }
	~Lerp() { stop(); }
	Lerp(const Lerp& copy) { *this = copy; play(); }
	
	Lerp<T>& operator=(const Lerp<T>& copy)
	{
		value = copy.value;
		target = copy.target;
		speed = copy.speed;
		return *this;
	}
	
	inline Lerp<T>& operator=(const T& v) { target = v; }
	inline operator const T&() const { return value; }
	
	inline void setValue(const T& v) { target = v; }
	inline const T& getValue() const { return value; }
	
	inline void setSpeed(float v) { speed = ofClamp(v, 0, 1); }
	inline float getSpeed() const { return speed; }
	
	inline Lerp<T>& operator+=(const T& v) { target += v; return *this; }
	inline Lerp<T>& operator-=(const T& v) { target -= v; return *this; }
	inline Lerp<T>& operator*=(const T& v) { target *= v; return *this; }
	inline Lerp<T>& operator/=(const T& v) { target /= v; return *this; }
	
protected:
	
	T value, target;
	float speed;
	
	void tick(float delta)
	{
		value += (target - value) * speed;
	}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE