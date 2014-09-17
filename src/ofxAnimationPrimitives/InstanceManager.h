#pragma once

#include "ofMain.h"

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class InstanceManager;

class Instance
{
	friend class InstanceManager;
	
public:
	
	Instance() : class_id(0), remain(0), duration(0), life(0), one_minus_life(0), after(0) {}
	virtual ~Instance() {}
	
	virtual void update() {}
	virtual void draw() {}
	
	inline void play(float duration, float after = 0)
	{
		if (duration < 0) duration = 0;
		this->duration = remain = duration;
		this->after = after;
	}

	inline void playInfinity()
	{
		this->duration = remain = std::numeric_limits<float>::infinity();
	}
	
	// use with playInfinity
	void release(float duration)
	{
		this->duration = remain = duration;
	}

public:
	
	inline bool isAlive() const { return remain > 0; }
	
	inline float getLife() const { return life; }
	inline float getOneMinusLife() const { return one_minus_life; }
	inline float getInvLife() const { return getOneMinusLife(); }
	
	inline float getDuration() const { return duration; }
	
	inline bool isInfinity() const { return std::isinf(duration); }
	
protected:
	
	virtual void willDelete() {}

private:
	
	RTTI::TypeID class_id;
	
	float remain;
	float duration;
	float after;
	
	// cache
	float life;
	float one_minus_life;

};

class InstanceManager
{
public:
	
	void update(float tick = ofGetLastFrameTime())
	{
		for (int i = 0; i < instances.size(); i++)
		{
			Instance *o = instances[i];
			
			if (o->after >= tick)
			{
				o->after -= tick;
				continue;
			}
			else o->after = 0;
			
			o->update();
			o->remain -= tick;
			
			if (isnormal(o->duration))
				o->life = o->remain / o->duration;
			else
				o->life = 1;
				
			o->one_minus_life = 1 - o->life;
		}
		
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			if (!o->isAlive())
			{
				it = instances.erase(it);
				o->willDelete();
				delete o;
			}
			else
				it++;
		}
	}
	
	void draw()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		ofPushMatrix();
		ofPushStyle();
		
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			if (o->after == 0)
				o->draw();
			it++;
		}
		
		ofPopStyle();
		ofPopMatrix();
		glPopAttrib();
	}
	
public:
	
	template <typename T>
	T* createInstance()
	{
		return setupInstance(new T);
	}
	
	/*
	http://nedbatchelder.com/code/cog/
	$ cog.py -r SomoSourceCode.h

	[[[cog
	import cog
	
	tmpl = '''template <typename T, %(A)s>
	T* createInstance(%(B)s)
	{
		return setupInstance<T>(new T(%(C)s));
	}
	'''
	
	cog.outl('')
	for i in xrange(1, 18):
		a = ', '.join(['typename A%i' % x for x in range(i)])
		b = ', '.join(['const A%i& a%i' % (x, x) for x in range(i)])
		c = ', '.join(['a%i' % x for x in range(i)])
		cog.outl(tmpl % {'A':a, 'B':b, 'C':c})
	
	]]]*/

	template <typename T, typename A0>
	T* createInstance(const A0& a0)
	{
		return setupInstance<T>(new T(a0));
	}

	template <typename T, typename A0, typename A1>
	T* createInstance(const A0& a0, const A1& a1)
	{
		return setupInstance<T>(new T(a0, a1));
	}

	template <typename T, typename A0, typename A1, typename A2>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2)
	{
		return setupInstance<T>(new T(a0, a1, a2));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
	}

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
	T* createInstance(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15, const A16& a16)
	{
		return setupInstance<T>(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
	}

	//[[[end]]]

	template <typename T>
	void release()
	{
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			if (o->class_id == RTTI::getTypeID<T>())
			{
				it = instances.erase(it);
				o->willDelete();
				delete o;
			}
			else
				it++;
		}
	}

	template <typename T>
	void release(float duration)
	{
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			if (o->class_id == RTTI::getTypeID<T>())
			{
				o->release(duration);
			}
			it++;
		}
	}

	void clear()
	{
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			delete o;
			it++;
		}
		
		instances.clear();
	}
	
	template <typename T>
	vector<T*> getInstance()
	{
		vector<T*> result;
		
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			if (o->class_id == RTTI::getTypeID<T>())
			{
				result.push_back((T*)o);
			}
			it++;
		}
		
		return result;
	}
	
protected:
	
	vector<Instance*> instances;
	
	template <typename T>
	T* setupInstance(T* o)
	{
		o->class_id = RTTI::getTypeID<T>();
		instances.push_back(o);
		return o;
	}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE