#pragma once

#include "Constants.h"

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

namespace Easing {

struct Back
{
	inline static float easeIn(const float t)
	{
		return 3 * t * t * t - 2 * t * t;
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Bounce
{

	inline static float easeIn(const float t)
	{
		static const float DH = 1. / 22.;
		static const float D1 = 1. / 11.;
		static const float D2 = 2. / 11.;
		static const float D3 = 3. / 11.;
		static const float D4 = 4. / 11.;
		static const float D5 = 5. / 11.;
		static const float D7 = 7. / 11.;
		static const float IH = 1. / DH;
		static const float I1 = 1. / D1;
		static const float I2 = 1. / D2;
		static const float I4D = 1. / D4 / D4;

		float s;
		if (t < D1)
		{
			s = t - DH;
			s = DH - s * s * IH;
		}
		else if (t < D3)
		{
			s = t - D2;
			s = D1 - s * s * I1;
		}
		else if (t < D7)
		{
			s = t - D5;
			s = D2 - s * s * I2;
		}
		else
		{
			s = t - 1;
			s = 1 - s * s * I4D;
		}
		return s;
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}

};

struct Circ
{
	inline static float easeIn(const float t)
	{
		return 1.0 - sqrtf(1.0 - t * t);
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Cubic
{
	inline static float easeIn(const float t)
	{
		return t * t * t;
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Elastic
{
	inline static float easeIn(const float t)
	{
		return 1.0 - easeOut(1.0 - t);
	}
	
	inline static float easeOut(const float t)
	{
		float s = 1 - t;
		return 1 - powf(s, 8) + sinf(t * t * 6 * PI) * s * s;
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Expo
{
	inline static float easeIn(const float t)
	{
		return powf(2, 10 * (t - 1));
	}
	
	inline static float easeOut(const float t)
	{
		return 1.0 - powf(2, -10 * t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Linear
{
	inline static float easeIn(const float t)
	{
		return t;
	}
	
	inline static float easeOut(const float t)
	{
		return t;
	}
	
	inline static float easeInOut(const float t)
	{
		return t;
	}
};

struct Quad
{
	inline static float easeIn(const float t)
	{
		return t * t;
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Quart
{
	inline static float easeIn(const float t)
	{
		return t * t * t * t;
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Quint
{
	inline static float easeIn(const float t)
	{
		return t * t * t * t * t;
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

struct Sine
{
	inline static float easeIn(const float t)
	{
		return 1.0 - cosf(t * HALF_PI);
	}
	
	inline static float easeOut(const float t)
	{
		return 1. - easeIn(1. - t);
	}
	
	inline static float easeInOut(const float t)
	{
		return (t < 0.5) ? easeIn(t * 2.0) * 0.5 : 1 - easeIn(2.0 - t * 2.0) * 0.5;
	}
};

}

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE