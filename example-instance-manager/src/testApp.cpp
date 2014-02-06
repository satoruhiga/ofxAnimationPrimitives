#include "testApp.h"

#include "ofxAnimationPrimitives.h"

int num_instance = 0;

class MyInstance : public ofxAnimationPrimitives::Instance
{
public:
	
	ofVec2f pos;
	ofColor color;
	float phase;
	
	MyInstance(float x, float y)
	{
		pos.set(x, y);
		color = ofColor::fromHsb(ofRandom(255), 255, 255);
		phase = 0;
		
		cout << "created: " << ++num_instance << endl;
	}
	
	~MyInstance()
	{
		cout << "deleted: " << --num_instance << endl;
	}
	
	void update()
	{
		phase += 0.05;
	}
	
	void draw()
	{
		ofFill();
		ofSetColor(color);
		ofCircle(pos, (30 + sin(phase * PI) * 10) * getLife());
	}
};

class MyInfinityInstance : public ofxAnimationPrimitives::Instance
{
public:
	
	ofVec2f pos;
	ofColor color;
	float phase;
	float mass;
	
	MyInfinityInstance(float x, float y)
	{
		pos.set(x, y);
		color = ofColor::fromHsb(ofRandom(255), 255, 255);
		phase = 0;
		mass = ofRandom(0.01, 0.1);
		
		cout << "created: " << ++num_instance << endl;
	}
	
	~MyInfinityInstance()
	{
		cout << "deleted: " << --num_instance << endl;
	}
	
	void update()
	{
		phase += 0.01;
		pos += (ofVec2f(ofGetMouseX(), ofGetMouseY()) - pos) * mass;
	}
	
	void draw()
	{
		ofNoFill();
		ofSetColor(color);
		ofCircle(pos, (100 + sin(phase * PI) * 30) * getLife());
	}
};


ofxAnimationPrimitives::InstanceManager manager;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
}

//--------------------------------------------------------------
void testApp::update()
{
	manager.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
	manager.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	manager.release<MyInfinityInstance>(3);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	manager.createInstance<MyInstance>(x, y)->play(4);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	manager.createInstance<MyInfinityInstance>(x, y)->playInfinity();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}