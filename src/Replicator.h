#pragma once

#include "ofMain.h"

#include "ofxAnimationPrimitivesUtils.h"

BEGIN_OFX_ANIMATION_PRIMITIVES_NAMESPACE

template <typename ParamType>
struct Replicator_
{
	typedef Replicator_ Replicator;
	
	// base classes
	class Node;
	class Operator;
	class Layout;
	
	// layout
	class Linear;
	class Fill2D;
	class Grid2D;
	class Grid3D;
	
	inline size_t size() const { return children.size(); }
	inline Node& get(size_t i) { return children[i]; }
	inline Node& operator[](size_t i) { return children[i]; }
	
	void resize(size_t num)
	{
		children.resize(num);
		for (int i = 0; i < children.size(); i++)
		{
			children[i].id = i;
		}
	}

protected:
	
	vector<Node> children;
};

#pragma mark - Base Classes

template <typename T>
class Replicator_<T>::Operator
{
public:
	
	virtual void operator()(Replicator &repl) {}
	
	Replicator& apply(Replicator &repl)
	{
		this->operator()(repl);
		return repl;
	}
};

template <typename T>
struct Replicator_<T>::Node
{
	friend struct Replicator_;
	
public:
	
	struct Operator;
	
	T param;
	
	ofMatrix4x4 m;
	
	inline int getID() const { return id; }
	inline void beginTransform()
	{
		ofPushMatrix();
		ofMultMatrix(m);
	}
	
	inline void endTransform()
	{
		ofPopMatrix();
	}

private:
	
	int id;
	
};

template <typename T>
class Replicator_<T>::Node::Operator
{
public:
	
	virtual void operator()(Node &node) {}

	Replicator& apply(Replicator &repl)
	{
		for (int i = 0; i < repl.size(); i++)
			this->operator()(repl[i]);
		
		return repl;
	}
};

#pragma mark - Layout

template <typename T>
struct Replicator_<T>::Linear : public Operator
{
	int count;
	ofVec3f offset;
	
	Linear(int count, ofVec3f offset) : count(count), offset(offset) {}
	
	void operator()(Replicator &repl)
	{
		repl.resize(count);
		
		float d = 0;
		for (int i = 0; i < repl.size(); i++)
		{
			repl[i].m.setTranslation(i * offset);
		}
	}
};

template <typename T>
struct Replicator_<T>::Fill2D : public Operator
{
	int offsetX, offsetY;
	float sizeX, sizeY;
	
	Fill2D(int offsetX, int offsetY, float sizeX, float sizeY) : offsetX(offsetX), offsetY(offsetY), sizeX(sizeX), sizeY(sizeY) {}
	
	void operator()(Replicator &repl)
	{
		const int nX = sizeX / offsetX + 1;
		const int nY = sizeY / offsetY + 1;
		
		const int num = nX * nY;
		repl.resize(num);
		
		int idx = 0;
		for (int y = 0; y < nY; y++)
		{
			for (int x = 0; x < nX; x++)
			{
				repl[idx].m.setTranslation(x * offsetX, y * offsetY, 0);
				repl[idx].param.x = x;
				repl[idx].param.y = y;
				
				idx++;
			}
		}
	}
};

template <typename T>
struct Replicator_<T>::Grid2D : public Operator
{
	int X, Y;
	float sizeX, sizeY;
	
	Grid2D(int X, int Y, float sizeX, float sizeY) : X(X), Y(Y), sizeX(sizeX), sizeY(sizeY) {}
	
	void operator()(Replicator &repl)
	{
		const int X_minus_one = X - 1;
		const int Y_minus_one = Y - 1;
		
		const int num = X * Y;
		repl.resize(num);
		
		int idx = 0;
		for (int y = 0; y < Y; y++)
		{
			for (int x = 0; x < X; x++)
			{
				float xx = ofMap(x, 0, X_minus_one, 0, 1) * sizeX;
				float yy = ofMap(y, 0, Y_minus_one, 0, 1) * sizeY;
				
				repl[idx].m.setTranslation(xx, yy, 0);
				repl[idx].param.x = x;
				repl[idx].param.y = y;
				
				idx++;
			}
		}
	}
};

template <typename T>
struct Replicator_<T>::Grid3D : public Operator
{
	int X, Y, Z;
	float sizeX, sizeY, sizeZ;
	
	Grid3D(int X, int Y, int Z, float sizeX, float sizeY, float sizeZ) : X(X), Y(Y), Z(Z), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) {}
	
	void operator()(Replicator &repl)
	{
		const int X_minus_one = X - 1;
		const int Y_minus_one = Y - 1;
		const int Z_minus_one = Z - 1;
		
		const int num = X * Y * Z;
		repl.resize(num);
		
		int idx = 0;
		
		for (int z = 0; z < Z; z++)
		{
			for (int y = 0; y < Y; y++)
			{
				for (int x = 0; x < X; x++)
				{
					float xx = ofMap(x, 0, X_minus_one, 0, 1) * sizeX;
					float yy = ofMap(y, 0, Y_minus_one, 0, 1) * sizeY;
					float zz = ofMap(z, 0, Z_minus_one, 0, 1) * sizeZ;
					
					repl[idx].m.setTranslation(xx, yy, zz);
					repl[idx].param.x = x;
					repl[idx].param.y = y;
					repl[idx].param.z = z;

					idx++;
				}
			}
		}
	}
};

END_OFX_ANIMATION_PRIMITIVES_NAMESPACE