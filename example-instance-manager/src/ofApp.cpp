#include "ofApp.h"

#include "ofxAnimationPrimitives.h"

int num_instance = 0;

class MyInstance : public ofxAnimationPrimitives::Instance
{
public:
	
    glm::vec2 pos;
	ofColor color;
	float phase;
	
	MyInstance(float _x, float _y)
	{

		pos.x = _x;
        pos.y = _y;
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
        ofDrawCircle(pos, (30 + sin(phase * PI) * 10) * getLife());
	}
};

class MyInfinityInstance : public ofxAnimationPrimitives::Instance
{
public:
	
	glm::vec2 pos;
	ofColor color;
	float phase;
	float mass;
	
	MyInfinityInstance(float _x, float _y)
	{
        pos.x = _x;
        pos.y = _y;
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
        pos = pos + (glm::vec2(ofGetMouseX(), ofGetMouseY()) - pos) * mass;
	}
	
	void draw()
	{
        ofNoFill();
        ofSetColor(color);
        ofDrawCircle(pos, (100 + sin(phase * PI) * 30) * getLife());
	}
};


ofxAnimationPrimitives::InstanceManager manager;

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update()
{
	manager.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	manager.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	manager.release<MyInfinityInstance>(3);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	manager.createInstance<MyInstance>(x, y)->play(4);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	manager.createInstance<MyInfinityInstance>(x, y)->playInfinity();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
