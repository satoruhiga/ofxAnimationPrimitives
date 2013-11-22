#pragma once

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class InstanceManager;

class Instance
{
	friend class InstanceManager;
	
public:
	
	virtual ~Instance() {}
	
	virtual void update() {}
	virtual void draw() {}
	
	void play(float duration)
	{
		this->duration = remain = duration;
	}
	
public:
	
	bool isAlive() const { return remain > 0; }
	
	float getLife() const { return life; }
	float getOneMinusLife() const { return one_minus_life; }
	
	float getDuration() const { return duration; }
	
protected:
	
	unsigned int class_id;
	
	float remain;
	float duration;
	
	// cache
	float life;
	float one_minus_life;
	
	virtual void willDelete() {}

};

class InstanceManager
{
public:
	
	void update(float tick = ofGetLastFrameTime())
	{
		for (int i = 0; i < instances.size(); i++)
		{
			Instance *o = instances[i];
			o->update();
			o->remain -= tick;
			o->life = o->remain / o->duration;
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
		ofPushStyle();
		
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			o->draw();
			it++;
		}
		
		ofPopStyle();
	}
	
public:
	
	template <typename T>
	T* create()
	{
		T *o = new T;
		o->class_id = Type2Int<T>::value();
		instances.push_back(o);
		return o;
	}
	
	template <typename T>
	void killall()
	{
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			if (o->class_id == Type2Int<T>::value())
			{
				it = instances.erase(it);
				o->willDelete();
				delete o;
			}
			else
				it++;
		}
	}
	
	void clear()
	{
		vector<Instance*>::iterator it = instances.begin();
		while (it != instances.end())
		{
			Instance *o = *it;
			o->willDelete();
			delete o;
			it++;
		}
		
		instances.clear();
	}
	
protected:
	
	vector<Instance*> instances;
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE