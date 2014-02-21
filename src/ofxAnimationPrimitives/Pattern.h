#pragma once

#include "ofMain.h"

#include "Constants.h"
#include "Timer.h"

// based SuperCollider sequence mechanism
// see. http://doc.sccode.org/Tutorials/Getting-Started/16-Sequencing-with-Patterns.html

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class Pattern
{
public:
	
	typedef float value_type;
	typedef ofPtr<Pattern> Ref;
	
	Pattern() {}
	Pattern(const float& value) : value(value) {}
	
	virtual bool valid() const { return true; }
	virtual void next() { if (valid()) update(); }
	
	const value_type& get() const { return value; }
	
protected:
	
	value_type value;
	virtual void update() {}
};

class ListPattern : public Pattern
{
public:
	
	ListPattern() : num(0) {}
	ListPattern(int num) : num(num) {}
	
	bool valid() const { return num > 0 || num == -1; }
	
protected:
	
	int num;
	void tick() { if (num > 0) num--; }
	
};

class Rand : public ListPattern
{
	vector<value_type> elem;
	
public:
	
	Rand() {}
	Rand(const vector<value_type>& elem, int num = -1) : elem(elem), ListPattern(num)
	{
		this->value = this->elem[rand() % this->elem.size()];
	}
	
protected:
	
	void update()
	{
		ListPattern::tick();
		this->value = this->elem[rand() % this->elem.size()];
	}
};

class Seq : public ListPattern
{
	int count;
	vector<value_type> elem;
	
public:
	
	Seq() {}
	Seq(const vector<value_type>& elem, int num = -1) : elem(elem), ListPattern(num), count(0)
	{
		this->value = this->elem[0];
	}
	
protected:
	
	void update()
	{
		ListPattern::tick();
		this->value = this->elem[++count % this->elem.size()];
	}
};

class While : public ListPattern
{
	int count;
	value_type min, max;
	
public:
	
	While() {}
	While(const value_type& min, const value_type& max, int num = -1) : min(min), max(max), ListPattern(num), count(0)
	{
		this->value = ofLerp(min, max, ofRandom(1));
	}
	
protected:
	
	void update()
	{
		ListPattern::tick();
		this->value = ofLerp(min, max, ofRandom(1));
	}
};

// time

class TimePattern : public Pattern, public Ticker
{
public:
	
	TimePattern() :remain(0), playing(false), value_pattern(NULL), dur_pattern(NULL) {}
	
	virtual ~TimePattern()
	{
		stop();
		
		if (value_pattern)
			delete value_pattern;
		
		if (dur_pattern)
			delete dur_pattern;
	}
	
	void play()
	{
		playing = true;
		Ticker::play();
	}
	
	void pause() { playing = false; }
	
	void stop()
	{
		Ticker::stop();
		remain = 0;
		playing = false;
	}
	
	void toggle() { isPlaying() ? stop() : play(); }
	
	bool isPlaying() { return playing; }
	
	bool valid() const
	{
		return value_pattern->valid()
			&& dur_pattern->valid();
	}
	
protected:
	
	virtual void event() {}
	
protected:
	
	float remain;
	bool playing;

	void setPattern(Pattern *value, Pattern *dur)
	{
		setValuePattern(value);
		setDurationPattern(dur);
	}
	
	void setValuePattern(Pattern *value)
	{
		if (value_pattern)
			delete value_pattern;
		value_pattern = value;
	}
	
	void setDurationPattern(Pattern *dur)
	{
		if (dur_pattern)
			delete dur_pattern;
		dur_pattern = dur;
	}
	
	void tick(float delta)
	{
		// must set value_pattern & dur_pattern
		assert(value_pattern);
		assert(dur_pattern);
		
		if (!valid()) stop();
		
		if (!playing) return;
		
		bool fire = false;
		while (remain <= 0)
		{
			remain += dur_pattern->get();
			dur_pattern->next();
			fire = true;
		}
		
		if (fire)
		{
			this->value = value_pattern->get();
			value_pattern->next();
			
			this->event();
		}
		
		remain -= delta;
	}

private:
	
	Pattern *value_pattern;
	Pattern *dur_pattern;

};

class Step : public TimePattern
{
public:
	
	Step() {}
	
	template <typename T0, typename T1>
	Step(const T0& value, const T1& dur)
	{
		setValuePattern(new T0(value));
		setDurationPattern(new T1(dur));
	}
	
};

//

class Bind : public Pattern
{
	map<string, Pattern::Ref> patterns;
	map<string, Pattern::value_type> value;
	
public:
	
	typedef map<string, Pattern::value_type> value_type;
	
	Bind() {}
	
	template <typename T0>
	Bind(const string& key0, const T0& t0)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
	}
	
	template <typename T0, typename T1>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
	}
	
	template <typename T0, typename T1, typename T2>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
	}
	
	template <typename T0, typename T1, typename T2, typename T3>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2, const string& key3, const T3& t3)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
		patterns[key3] = Pattern::Ref(new T3(t3));
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2, const string& key3, const T3& t3, const string& key4, const T4& t4)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
		patterns[key3] = Pattern::Ref(new T3(t3));
		patterns[key4] = Pattern::Ref(new T4(t4));
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2, const string& key3, const T3& t3, const string& key4, const T4& t4, const string& key5, const T5& t5)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
		patterns[key3] = Pattern::Ref(new T3(t3));
		patterns[key4] = Pattern::Ref(new T4(t4));
		patterns[key5] = Pattern::Ref(new T5(t5));
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2, const string& key3, const T3& t3, const string& key4, const T4& t4, const string& key5, const T5& t5, const string& key6, const T6& t6)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
		patterns[key3] = Pattern::Ref(new T3(t3));
		patterns[key4] = Pattern::Ref(new T4(t4));
		patterns[key5] = Pattern::Ref(new T5(t5));
		patterns[key6] = Pattern::Ref(new T6(t6));
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2, const string& key3, const T3& t3, const string& key4, const T4& t4, const string& key5, const T5& t5, const string& key6, const T6& t6, const string& key7, const T7& t7)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
		patterns[key3] = Pattern::Ref(new T3(t3));
		patterns[key4] = Pattern::Ref(new T4(t4));
		patterns[key5] = Pattern::Ref(new T5(t5));
		patterns[key6] = Pattern::Ref(new T6(t6));
		patterns[key7] = Pattern::Ref(new T7(t7));
	}
	
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	Bind(const string& key0, const T0& t0, const string& key1, const T1& t1, const string& key2, const T2& t2, const string& key3, const T3& t3, const string& key4, const T4& t4, const string& key5, const T5& t5, const string& key6, const T6& t6, const string& key7, const T7& t7, const string& key8, const T8& t8)
	{
		patterns[key0] = Pattern::Ref(new T0(t0));
		patterns[key1] = Pattern::Ref(new T1(t1));
		patterns[key2] = Pattern::Ref(new T2(t2));
		patterns[key3] = Pattern::Ref(new T3(t3));
		patterns[key4] = Pattern::Ref(new T4(t4));
		patterns[key5] = Pattern::Ref(new T5(t5));
		patterns[key6] = Pattern::Ref(new T6(t6));
		patterns[key7] = Pattern::Ref(new T7(t7));
		patterns[key8] = Pattern::Ref(new T8(t8));
	}
	
	bool valid() const
	{
		map<string, Pattern::Ref>::const_iterator it = patterns.begin();
		
		while (it != patterns.end())
		{
			if (!it->second->valid()) return false;
			it++;
		}
		
		return true;
	}
	
	const Pattern::value_type& get(const string& key) { return value[key]; }
	
	void dump() const
	{
		map<string, Pattern::Ref>::const_iterator it = patterns.begin();
		
		cout << "[" << endl;
		while (it != patterns.end())
		{
			if (!it->second->valid());
			cout << "\t" << it->first << ": " << it->second->get() << endl;
			it++;
		}
		cout << "]" << endl;
	}
	
protected:
	
	void update()
	{
		map<string, Pattern::Ref>::const_iterator it = patterns.begin();
		
		while (it != patterns.end())
		{
			it->second->next();
			value[it->first] = it->second->get();
			it++;
		}
	}
	
};

// SuperCollider like typename

typedef Rand Prand;
typedef Seq Pseq;
typedef While Pwhile;
typedef Step Pstep;
typedef Bind Pbind;

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
