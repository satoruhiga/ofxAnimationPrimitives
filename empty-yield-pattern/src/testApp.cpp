#include "testApp.h"

#include "ofxAnimationPrimitives.h"

int sequence()
{
	static ofxAnimationPrimitives::Generator gen;
	
	$seq (gen)
	{
		yield return 1;
		yield return 2;
		yield return 3;
	}
	
	return -1;
}

int loop()
{
	static ofxAnimationPrimitives::Generator gen;
	
	$inf (gen)
	{
		yield return 1;
		yield return 2;
		yield return 3;
	}
	
	return -1;
}


//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0);
	
	cout << sequence() << endl; // get 1
	cout << sequence() << endl; // get 2
	cout << sequence() << endl; // get 3
	cout << sequence() << endl; // get -1
	cout << sequence() << endl; // get -1
	
	cout << endl;
	cout << "///" << endl;
	cout << endl;
	
	cout << loop() << endl; // get 1
	cout << loop() << endl; // get 2
	cout << loop() << endl; // get 3
	cout << loop() << endl; // get 1
	cout << loop() << endl; // get 2
	
	ofExit();
}

//--------------------------------------------------------------
void testApp::update()
{

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