#include "testApp.h"

#include "ofxAnimationPrimitives.h"

ofxAnimationPrimitives::Sequence seq;

class MyClip : public ofxAnimationPrimitives::Sequence::Clip
{
public:
	
	string name;
	float start_time;
	float duration;
	
	ofVec2f pos;
	
	MyClip(string name, float start_time, float duration)
	: name(name), start_time(start_time), duration(duration) {}
	
	float getStartTime() const { return start_time; }
	float getDuration() const { return duration; }

	
	
	void onStart()
	{
		cout << "start: " << name << endl;
		
		pos.x = ofRandomWidth();
		pos.y = ofRandomHeight();
	}
	
	void onEnd()
	{
		cout << "end: " << name << endl;
	}
	
	void draw()
	{
		ofSetColor(255);
		ofDrawBitmapString(name, pos);
		ofRect(pos.x, pos.y, 100, 100);
	}

};

class MyRedClip : public MyClip
{
public:
	
	MyRedClip(string name, float start_time, float duration) : MyClip(name, start_time, duration) {}
	
	void onStart()
	{
		cout << "red start: " << name << endl;
		
		pos.x = ofRandomWidth();
		pos.y = ofRandomHeight();
	}
	
	void onEnd()
	{
		cout << "red end: " << name << endl;
	}

	void draw()
	{
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(name, pos);
		ofRect(pos.x, pos.y, 100, 100);
	}
};

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	
	seq.addClip(new MyClip("clip0", 1, 1));
	seq.addClip(new MyClip("clip1", 1.5, 1));
	seq.addClip(new MyClip("clip2", 2, 1));
	
	seq.addClip(new MyRedClip("clip3", 3, 2));
}

//--------------------------------------------------------------
void testApp::update()
{
	seq.setTime(fmodf(ofGetElapsedTimef(), 4));
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofSetColor(255);
	ofDrawBitmapString(ofToString(fmodf(ofGetElapsedTimef(), 4), 1), 10, 20);
	
	const vector<ofxAnimationPrimitives::Sequence::Clip::Ref>& clips = seq.getActiveClips();
	for (int i = 0; i < clips.size(); i++)
	{
		clips[i]->draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	seq.setTime(0);
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