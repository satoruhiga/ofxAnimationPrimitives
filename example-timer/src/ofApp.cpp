#include "ofApp.h"

#include "ofxAnimationPrimitives.h"

ofxAnimationPrimitives::Timer oneshot;
ofxAnimationPrimitives::Timer repeat;

void ofApp::onOneshotTimerEvent(int&)
{
	ofBackground(255, 0, 0);
	cout << "oneshot: " << ofGetElapsedTimef() << endl;
}

void ofApp::onRepeatTimerEvent(int&)
{
	ofBackground(255);
	cout << "repeat: " << ofGetElapsedTimef() << endl;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	
	ofAddListener(oneshot.timerEvent, this, &ofApp::onOneshotTimerEvent);
	ofAddListener(repeat.timerEvent, this, &ofApp::onRepeatTimerEvent);
	
	repeat.start(1, ofxAnimationPrimitives::Timer::FOREVER);
	oneshot.start(0.5, 1);
}

//--------------------------------------------------------------
void ofApp::update()
{
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::draw()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
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
	oneshot.start(1, false);
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
