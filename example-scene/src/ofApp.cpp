#include "ofApp.h"

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
		ofDrawRectangle(0, 0, ofGetWidth() / 2, ofGetHeight());
		
		ofSetColor(255);
		ofDrawBitmapString("SCENE0 alpha:" + ofToString(getAlpha(), 3), 10, 20);
	}
	
	void viewWillAppear() { cout << __PRETTY_FUNCTION__ << endl; }
	void viewDidAppear() { cout << __PRETTY_FUNCTION__ << endl; }
	void viewWillDisappear() { cout << __PRETTY_FUNCTION__ << endl; }
	void viewDidDisappear() { cout << __PRETTY_FUNCTION__ << endl; }
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
		ofDrawRectangle(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
		
		ofSetColor(255);
		ofDrawBitmapString("SCENE1 alpha:" + ofToString(getAlpha(), 3), ofGetWidth() / 2 + 10, 20);
	}
	
	void viewWillAppear() { cout << __PRETTY_FUNCTION__ << endl; }
	void viewDidAppear() { cout << __PRETTY_FUNCTION__ << endl; }
	void viewWillDisappear() { cout << __PRETTY_FUNCTION__ << endl; }
	void viewDidDisappear() { cout << __PRETTY_FUNCTION__ << endl; }
};

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	
	SM.addScene<Scene0>(42);
	SM.addScene<Scene1>("'arg0 string'", PI);
	
	SM.changeScene("Scene0");
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofBackground(0);
	
	SM.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	SM.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '1') SM.changeScene<Scene0>(0.1);
	if (key == '2') SM.changeScene<Scene1>();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
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
