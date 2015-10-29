#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	textInputBox.m_strControlID	= "TextInputBox_Name";
	textInputBox.set(100, 100, 500, 70);
	textInputBox.enable(true);
	textInputBox.select(true);

	keyboard.showKeyboard(true);

	ofAddListener(ofxHangulKeyboard::KeyboardPressEvent, this, &ofApp::onKeyboardPressEvent);
}

//--------------------------------------------------------------
void ofApp::update(){

}


void ofApp::onKeyboardPressEvent(const void*pSender, int& keyCode)
{

	if(keyCode == OF_KEY_RETURN)
	{

	
	}
	else
	{
		textInputBox.keyDown(keyCode);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	keyboard.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}