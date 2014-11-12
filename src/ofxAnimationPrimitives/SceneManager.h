OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

class SceneManager;

#define OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(CLASS) \
static const char* getSceneName() { return #CLASS; }

class Scene
{
	friend class SceneManager;
	
public:
	
	Scene()
	: _alpha(0)
	{}
	
	virtual void update() {}
	virtual void draw() {}
	
	float getAlpha() const { return _alpha; }
	
private:
	
	float _alpha;
};

class SceneManager
{
public:
	
	SceneManager()
	: default_fade_duration(1)
	{}
	
	void update()
	{
		{
			map<Scene*, Fader>::iterator it = faders.begin();
			while (it != faders.end())
			{
				Fader& fader = it->second;
				fader.update();
				it++;
			}
		}
		
		{
			map<string, Scene*>::iterator it = scenes.begin();
			while (it != scenes.end())
			{
				Scene* scene = it->second;
				if (scene->getAlpha() > 0)
				{
					scene->update();
				}
				
				it++;
			}
		}
	}
	
	void draw()
	{
		map<string, Scene*>::iterator it = scenes.begin();
		while (it != scenes.end())
		{
			Scene* scene = it->second;
			if (scene->getAlpha() > 0)
			{
				ofPushMatrix();
				ofPushStyle();
				
				scene->draw();
				
				ofPopStyle();
				ofPopMatrix();
			}
			
			it++;
		}
	}
	
	template <typename T>
	void addScene();
	
	/*
	http://nedbatchelder.com/code/cog/
	$ cog.py -r SomoSourceCode.h
	
	[[[cog
	import cog
	
	tmpl = '''template <typename T, %(A)s>
	void addScene(%(B)s);
	'''
	
	cog.outl('')
	for i in xrange(1, 18):
		a = ', '.join(['typename A%i' % x for x in range(i)])
		b = ', '.join(['const A%i& a%i' % (x, x) for x in range(i)])
		cog.outl(tmpl % {'A':a, 'B':b})
	
	]]]*/

	template <typename T, typename A0>
	void addScene(const A0& a0);

	template <typename T, typename A0, typename A1>
	void addScene(const A0& a0, const A1& a1);

	template <typename T, typename A0, typename A1, typename A2>
	void addScene(const A0& a0, const A1& a1, const A2& a2);

	template <typename T, typename A0, typename A1, typename A2, typename A3>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15);

	template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
	void addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15, const A16& a16);

	//[[[end]]]

	bool changeScene(const string& scene_name);
	bool changeScene(const string& scene_name, float fade_duration);
	
	template<typename T>
	bool changeScene();
	
	template<typename T>
	bool changeScene(float fade_duration);
	
	size_t getNumScenes() const { return scenes.size(); }
	const vector<string>& getSceneNames() const { return scene_names; }
	
	float setDefaultFadeDuration(float v) { default_fade_duration = v; }
	float getDefaultFadeDuration() const { return default_fade_duration; }
	
protected:
	
	map<string, Scene*> scenes;
	vector<string> scene_names;
	
	float default_fade_duration;
	
	class Fader
	{
	public:
		
		Fader() {}
		
		Fader(Scene* scene)
		: scene(scene)
		{}
		
		void fade(float target, float duration)
		{
			if (target == scene->_alpha) return;
			
			if (duration <= 0)
			{
				this->duration = 0;
				this->target_alpha = target;
				this->start_alpha = scene->_alpha;
				
				scene->_alpha = target;
				
				time = std::numeric_limits<float>::infinity();
			}
			else
			{
				this->duration = duration;
				this->target_alpha = target;
				this->start_alpha = scene->_alpha;
				
				time = 0;
			}
		}
		
		void update()
		{
			if (isActive() == false) return;
			
			time += ofGetLastFrameTime();
			
			float d = ofMap(time, 0, duration, start_alpha, target_alpha, true);
			
			scene->_alpha = d;
		}
		
		bool isActive() const
		{
			return time < duration;
		}
		
	private:
		
		Scene* scene;
		
		float time;
		float duration;
		
		float start_alpha;
		float target_alpha;
	};
	
	map<Scene*, Fader> faders;
	
	bool registerScene(Scene* scene, const string& scene_name)
	{
		if (scenes.find(scene_name) != scenes.end())
		{
			ofLogError("SceneManager") << "duplicated scene name";
			delete scene;
			return false;
		}
		
		scenes[scene_name] = scene;
		faders[scene] = Fader(scene);
		
		scene_names.push_back(scene_name);
		
		return true;
	}
};

//

template <typename T>
inline void SceneManager::addScene()
{
	Scene* s = new T;
	registerScene(s, T::getSceneName());
}

/*
http://nedbatchelder.com/code/cog/
$ cog.py -r SomoSourceCode.h

[[[cog
import cog

tmpl = '''template <typename T, %(A)s>
inline void SceneManager::addScene(%(B)s)
{
	Scene* s = new T(%(C)s);
	registerScene(s, T::getSceneName());
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
inline void SceneManager::addScene(const A0& a0)
{
	Scene* s = new T(a0);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1>
inline void SceneManager::addScene(const A0& a0, const A1& a1)
{
	Scene* s = new T(a0, a1);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2)
{
	Scene* s = new T(a0, a1, a2);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3)
{
	Scene* s = new T(a0, a1, a2, a3);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
{
	Scene* s = new T(a0, a1, a2, a3, a4);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);
	registerScene(s, T::getSceneName());
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
inline void SceneManager::addScene(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15, const A16& a16)
{
	Scene* s = new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16);
	registerScene(s, T::getSceneName());
}

//[[[end]]]

inline bool SceneManager::changeScene(const string& scene_name, float fade_duration)
{
	map<string, Scene*>::iterator it = scenes.find(scene_name);
	if (it == scenes.end())
	{
		ofLogError("SceneManager") << "unknown scene name";
		return false;
	}
	
	Scene* scene = it->second;
	
	{
		map<Scene*, Fader>::iterator it = faders.begin();
		while (it != faders.end())
		{
			Fader& fader = it->second;
			
			if (it->first == scene)
			{
				fader.fade(1, fade_duration);
			}
			else
			{
				fader.fade(0, fade_duration);
			}
			
			it++;
		}
	}
	
	return true;
}

inline bool SceneManager::changeScene(const string& scene_name)
{
	changeScene(scene_name, default_fade_duration);
}

template<typename T>
inline bool SceneManager::changeScene(float fade_duration)
{
	changeScene(T::getSceneName(), fade_duration);
}

template<typename T>
inline bool SceneManager::changeScene()
{
	changeScene<T>(default_fade_duration);
}

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE
