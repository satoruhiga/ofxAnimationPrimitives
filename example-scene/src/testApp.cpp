#include "testApp.h"

#include "ofxAnimationPrimitives.h"

ofxAnimationPrimitives::SceneManager SM;

class Scene0 : public ofxAnimationPrimitives::Scene
{
public:
	
	OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene0);
	
	Scene0(const int arg0)
	{
		cout << "Scene0: " << arg0 << endl;
	}
	
	void update()
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}
	
	void draw()
	{
		ofSetColor(100, 0, 0, 255 * getAlpha());
		ofRect(0, 0, ofGetWidth() / 2, ofGetHeight());
		
		ofSetColor(255);
		ofDrawBitmapString("SCENE0 alpha:" + ofToString(getAlpha(), 3), 10, 20);
	}
};

class Scene1 : public ofxAnimationPrimitives::Scene
{
public:
	
	OFX_ANIMATION_PRIMITIVES_DEFINE_SCENE(Scene1);

	Scene1(const string& arg0, float arg1)
	{
		cout << "Scene1: " << arg0 << " " << arg1 << endl;
	}

	void update()
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}
	
	void draw()
	{
		ofSetColor(0, 100, 0, 255 * getAlpha());
		ofRect(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
		
		ofSetColor(255);
		ofDrawBitmapString("SCENE1 alpha:" + ofToString(getAlpha(), 3), ofGetWidth() / 2 + 10, 20);
	}
};

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	
	SM.addScene<Scene0>(42);
	SM.addScene<Scene1>("'arg0 string'", PI);
	
	SM.changeScene("Scene0");
}

//--------------------------------------------------------------
void testApp::update()
{
	ofBackground(0);
	
	SM.update();
}

//--------------------------------------------------------------
void testApp::draw()
{
	SM.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	if (key == '1') SM.changeScene<Scene0>(0.1);
	if (key == '2') SM.changeScene<Scene1>();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
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