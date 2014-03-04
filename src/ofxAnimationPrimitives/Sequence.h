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
	
	const vector<Clip::Ref>& getActiveClips() const { return active_clips_arr; }
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
	set<Clip::Ref> active_clips;
	vector<Clip::Ref> active_clips_arr;
	
	typedef multimap<float, Clip::Ref> ClipMap;
	ClipMap clip_map;
	
	void updateInRange(float start, float end)
	{
		if (start > end)
		{
			// remove future clip if play backwards
			
			set<Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				Clip::Ref o = *it;
				
				if (o->getStartTime() >= end)
				{
					o->onEnd();
					active_clips.erase(it++);
				}
				else it++;
			}
			
			return;
		}

		// Remove Pass 1: Find and remove out range clips
		{
			set<Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				Clip::Ref o = *it;
				
				if ((o->getStartTime() + o->getDuration()) <= end)
				{
					o->onEnd();
					active_clips.erase(it++);
				}
				else it++;
			}
		}

		// Find new in range clips
		{
			ClipMap::iterator it = clip_map.lower_bound(start);
			ClipMap::iterator end_it = clip_map.lower_bound(end);
			
			while (it != end_it)
			{
				Clip::Ref o = it->second;
				o->onStart();
				
				if (o->getDuration() > 0)
				{
					active_clips.insert(o);
				}
				else
				{
					o->onEnd();
				}
				
				it++;
			}
		}
		
		// Remove Pass 2: Find and remove in new clips
		{
			set<Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				Clip::Ref o = *it;
				
				if ((o->getStartTime() + o->getDuration()) <= end)
				{
					o->onEnd();
					active_clips.erase(it++);
				}
				else it++;
			}
		}
		
		active_clips_arr.assign(active_clips.begin(), active_clips.end());
	}
};

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
