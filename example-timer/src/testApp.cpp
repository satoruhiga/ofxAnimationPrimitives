#include "testApp.h"

#include "ofxAnimationPrimitives.h"

ofxAnimationPrimitives::Timer oneshot;
ofxAnimationPrimitives::Timer repeat;

void testApp::onOneshotTimerEvent(int&)
{
	ofBackground(255, 0, 0);
	cout << "oneshot: " << ofGetElapsedTimef() << endl;
}

void testApp::onRepeatTimerEvent(int&)
{
	ofBackground(255);
	cout << "repeat: " << ofGetElapsedTimef() << endl;
}

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	
	ofAddListener(oneshot.timerEvent, this, &testApp::onOneshotTimerEvent);
	ofAddListener(repeat.timerEvent, this, &testApp::onRepeatTimerEvent);
	
	repeat.start(1, ofxAnimationPrimitives::Timer::FOREVER);
	oneshot.start(0.5, 1);
}

//--------------------------------------------------------------
void testApp::update()
{
	ofBackground(0);
}

//--------------------------------------------------------------
void testApp::draw()
{
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
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
	oneshot.start(1, false);
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