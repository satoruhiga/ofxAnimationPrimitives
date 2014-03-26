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
	
	inline void setValue(const T& v, bool override = false) { override ? value = v : target = v; }
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

class Line : public Ticker
{
public:
	
	Line()
		:value(0)
		,value_delta(0)
		,curtime(0)
	{}
	
	/*
	 Max/MSP style lamp generator
	 
	 line.set("100 1 0 1"); // Value changes to 100 in 1 sec, then to 0 in 1 sec
	 line.play();
	 
	 // or
	 
	 line.play("0, 1000 0.5 -1000 0.5"); // Initialize value with comma and play immediately
	 */
	bool setup(const string& line_string)
	{
		string s = line_string;
		
		string::size_type n = s.find(",");
		if (n != string::npos)
		{
			value = ofToFloat(s.substr(0, n));
			s = s.substr(n + 1);
		}
		
		vector<string> e = ofSplitString(s, " ", true, true);
		if ((e.size() % 2) != 0) return false;
		
		arr.clear();
		
		for (int i = 0; i < e.size(); i += 2)
		{
			TimeValue TV;
			TV.value = ofToFloat(e[i]);
			TV.time = ofToFloat(e[i + 1]);
			arr.push_back(TV);
		}
		
		return true;
	}
	
	void play()
	{
		if (arr.empty())
		{
			ofLogError("Line") << "setup first";
			return;
		}
		
		curtime = 0;
		
		iter = arr.begin();
		updateDelta();
		
		Ticker::play();
	}
	
	void play(const string& line_string)
	{
		if (setup(line_string))
			play();
	}
	
	inline operator float() const { return value; }
	inline float getValue() const { return value; }
	
protected:
	
	float value;
	float value_delta;
	
	float curtime;
	
	struct TimeValue {
		float time;
		float value;
	};
	
	vector<TimeValue> arr;
	vector<TimeValue>::iterator iter;
	
	void updateDelta()
	{
		value_delta = (iter->value - value) / (iter->time - curtime);
	}

	void tick(float delta)
	{
		if (iter == arr.end()) return;
		
		value += value_delta * delta;
		
		if (curtime + delta < iter->time)
		{
			curtime += delta;
		}
		else
		{
			curtime = 0;
			value = iter->value;
			
			iter++;
			updateDelta();
		}
	}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
