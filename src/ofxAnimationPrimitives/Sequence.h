#pragma once

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class Sequence
{
public:
	
	class Clip
	{
	public:
		
		typedef Ref_<Clip> Ref;
		
		Clip() {}
		virtual ~Clip() {}
		
		virtual float getStartTime() const { return 0; }
		virtual float getDuration() const { return 0; }
		
		virtual void update() {}
		virtual void draw() {}
		
	public:
		
		virtual void onStart() {}
		virtual void onEnd() {}
	};

public:
	
	Sequence() : last_time(0) {}
	~Sequence() { clear(); }
	
	inline bool hasClip(Clip::Ref o)
	{
		return find(clips.begin(), clips.end(), o) != clips.end();
	}
	
	void addClip(Clip::Ref o)
	{
		if (hasClip(o)) return;
		clips.push_back(o);
		
		clip_map.insert(make_pair(o->getStartTime(), o));
	}
	
	void removeClip(Clip::Ref o)
	{
		if (!hasClip(o)) return;
		clips.erase(remove(clips.begin(), clips.end(), o), clips.end());
		
		// remove from clip_map
		int n = clip_map.count(o->getStartTime());
		if (n == 0) return;
		
		ClipMap::iterator it = clip_map.find(o->getStartTime());
		for (int i = 0; i < n; i++)
		{
			if (it->second == o)
			{
				clip_map.erase(it);
				break;
			}
			it++;
		}
	}
	
	void setTime(float t)
	{
		float begin = last_time;
		float end = t;
		
		if (begin != end)
			updateInRange(begin, end);
		
		last_time = t;
	}
	
	const vector<Clip::Ref>& getActiveClips() const { return active_clips; }
	const vector<Clip::Ref>& getAllClips() const { return clips; }
	
	void clear()
	{
		clips.clear();
		active_clips.clear();
		clip_map.clear();
	}
	
protected:
	
	float last_time;
	
	vector<Clip::Ref> clips;
	vector<Clip::Ref> active_clips;
	
	typedef multimap<float, Clip::Ref> ClipMap;
	ClipMap clip_map;
	
	void updateInRange(float start, float end)
	{
		// Find new in range clips
		{
			float start_t = start;
			float end_t = end;
			if (start_t > end_t) swap(start_t, end_t);
			
			ClipMap::iterator it = clip_map.lower_bound(start_t);
			ClipMap::iterator end_it = clip_map.lower_bound(end_t);
			
			while (it != end_it)
			{
				Clip::Ref o = it->second;
				
				active_clips.push_back(o);
				o->onStart();
				
				it++;
			}
		}
		
		// Find and remove out range clips
		{
			vector<Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				Clip::Ref o = *it;
				
				if (o->getDuration() <= 0
					|| o->getStartTime() > end
					|| (o->getStartTime() + o->getDuration()) < start)
				{
					o->onEnd();
					it = active_clips.erase(it);
				}
				else it++;
			}
		}
	}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
