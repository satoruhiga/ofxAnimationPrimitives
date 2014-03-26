#pragma once

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

template <typename timestamp_t>
class Sequence_
{
public:
	
	class Clip
	{
	public:
		
		typedef Ref_<Clip> Ref;
		
		Clip() {}
		virtual ~Clip() {}
		
		virtual timestamp_t getStartTime() const { return 0; }
		virtual timestamp_t getDuration() const { return 0; }
		
		virtual void update() {}
		virtual void draw() {}
		
	public:
		
		virtual void onStart() {}
		virtual void onEnd() {}
	};

public:
	
	Sequence_() : last_time(0) {}
	~Sequence_() { clear(); }
	
	inline bool hasClip(typename Clip::Ref o)
	{
		return find(clips.begin(), clips.end(), o) != clips.end();
	}
	
	void addClip(typename Clip::Ref o)
	{
		if (hasClip(o)) return;
		clips.push_back(o);
		
		clip_map.insert(make_pair(o->getStartTime(), o));
	}
	
	void removeClip(typename Clip::Ref o)
	{
		if (!hasClip(o)) return;
		clips.erase(remove(clips.begin(), clips.end(), o), clips.end());
		
		// remove from clip_map
		int n = clip_map.count(o->getStartTime());
		if (n == 0) return;
		
		typename ClipMap::iterator it = clip_map.find(o->getStartTime());
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
	
	void setTime(timestamp_t t)
	{
		timestamp_t begin = last_time;
		timestamp_t end = t;
		
		if (begin != end)
			updateInRange(begin, end);
		
		last_time = t;
	}
	
	const vector<typename Clip::Ref>& getActiveClips() const { return active_clips_arr; }
	const vector<typename Clip::Ref>& getAllClips() const { return clips; }
	
	void clear()
	{
		clips.clear();
		active_clips.clear();
		clip_map.clear();
	}
	
protected:
	
	timestamp_t last_time;
	
	vector<typename Clip::Ref> clips;
	set<typename Clip::Ref> active_clips;
	vector<typename Clip::Ref> active_clips_arr;
	
	typedef multimap<timestamp_t, typename Clip::Ref> ClipMap;
	ClipMap clip_map;
	
	void updateInRange(timestamp_t start, timestamp_t end)
	{
		if (start > end)
		{
			// remove future clip if play backwards
			
			typename set<typename Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				typename Clip::Ref o = *it;
				
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
			typename set<typename Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				typename Clip::Ref o = *it;
				
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
			typename ClipMap::iterator it = clip_map.lower_bound(start);
			typename ClipMap::iterator end_it = clip_map.lower_bound(end);
			
			while (it != end_it)
			{
				typename Clip::Ref o = it->second;
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
			typename set<typename Clip::Ref>::iterator it = active_clips.begin();
			while (it != active_clips.end())
			{
				typename Clip::Ref o = *it;
				
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

typedef Sequence_<float> Sequence;

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
