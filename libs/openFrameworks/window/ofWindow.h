#pragma once

#include <ofBaseApp.h>
#include "ofAppBaseWindow.h"
#include <GL/glfw3.h>
#include <map>
#include "ofWindowEvents.h"

#define OF_MAX_NUM_KEYS 512

/*****************
/ WINDOW LISTENER
*******************/

class ofWindowListener: public ofBaseApp
{
public:
	virtual void setup(ofWindow* f) {
		setup();
	}
	virtual void setup() {};
	virtual void update(ofWindow* f) {
		update();
	}
	virtual void update() {};
	virtual void draw(ofWindow* f) {
		draw();
	}
	virtual void draw() {};
	virtual void keyPressed(int key, ofWindow* f) {
		keyPressed(key);
	}

	//KEY
	virtual void keyPressed(int key) {};
	virtual void keyReleased(int key, ofWindow* f) {
		keyReleased(key);
	}
	virtual void keyReleased(int key) {};

	//WINDOW
	virtual void windowMoved(int x, int y, ofWindow* f) {
		windowMoved(x, y);
	}
	virtual void windowMoved(int x, int y) {};
	
	virtual void windowResized(int w, int h, ofWindow* f) {
		windowResized(w, h);
	}
	virtual void windowResized(int w, int h) {};

	//MOUSE
	virtual void mouseMoved(int x, int y, ofWindow* f) {
		mouseMoved(x, y);
	}
	virtual void mouseMoved(int x, int y) {};
	virtual void mouseDragged(int x, int y, int button,  ofWindow* f) {
		mouseDragged(x, y, button);
	}
	virtual void mouseDragged(int x, int y, int button) {};
	virtual void mousePressed(int x, int y, int btn, ofWindow* f) {
		mousePressed(x, y, btn);
	}
	virtual void mousePressed(int x, int y, int btn) {};
	virtual void mouseReleased(int x, int y, int btn, ofWindow* f) {
		mouseReleased(x, y, btn);
		mouseReleased();
	}
	virtual void mouseReleased(int x, int y, int btn) {}
	virtual void mouseReleased() {};

	virtual void scrolled(float deltaX, float deltaY, ofWindow* win){
		scrolled(deltaX, deltaY);
	}
	virtual void scrolled(float deltaX, float deltaY){};

	virtual void dragEvent(ofDragInfo info, ofWindow* f){dragEvent(info);}
	virtual void dragEvent(ofDragInfo info){}

	bool isUpdated;
};

///////////////////////////////////////////
// HELPERS FOR ofRunFensterApp

class ofWindowToOfBaseApp: public ofWindowListener{

public:
	ofWindowToOfBaseApp(ofBaseApp* base){
		mouseX = mouseY = 0;
		baseApp = base;
	}

	void setup(){
		baseApp->setup();
	}
	void update(){
		baseApp->update();
	}
	void draw(){
		baseApp->draw();
	}
	void exit(){
		baseApp->exit();
	}

	void windowResized(int w, int h){
		baseApp->windowResized(w, h);
	}

	void keyPressed( int key ){
		baseApp->keyPressed(key);
	}
	void keyReleased( int key ){
		baseApp->keyReleased(key);
	}

	void mouseMoved( int x, int y ){
		baseApp->mouseX = x;
		baseApp->mouseY = y;
		baseApp->mouseMoved(x, y);
	}
	void mouseDragged( int x, int y, int button ){
		baseApp->mouseX = x;
		baseApp->mouseY = y;
		baseApp->mouseDragged(x, y, button);
	}
	void mousePressed( int x, int y, int button ){
		baseApp->mouseX = x;
		baseApp->mouseY = y;
		baseApp->mousePressed(x, y, button);
	}
	void mouseReleased(){
		baseApp->mouseReleased();
	}
	void mouseReleased(int x, int y, int button ){
		baseApp->mouseX = x;
		baseApp->mouseY = y;
		baseApp->mouseReleased(x, y, button);
	}

	void dragEvent(ofDragInfo dragInfo) {
		baseApp->dragEvent(dragInfo);
	}
	void gotMessage(ofMessage msg){
		baseApp->gotMessage(msg);
	}

private:
	ofBaseApp* baseApp;
};

typedef std::vector<ofWindowListener*> ofWindowListenerList;

/*****************
/ WINDOW
*******************/

class ofWindow: public ofAppBaseWindow, protected ofRectangle{
public:
	ofWindow();
	~ofWindow();  
    
	void enableContext();
	void initializeWindow();
	
	void setWindowPositionAndShape(ofRectangle rect);
	void setWindowPositionAndShape(int x, int y, int width, int height); 

	void addListener(ofWindowListener* listener);
	void addListener(ofBaseApp* app);

	void setup();

	void update(ofEventArgs& e);
	void update();
	void draw(ofEventArgs& e);
	void draw();
	
	ofPoint	getWindowPosition();
	void setWindowPosition(int x, int y);
	void setWindowPosition(ofPoint pos);
	
	ofPoint	getWindowSize();
	void setWindowShape(int x, int y);
	void setWidth(int w);
	void setHeight(int h);
	
	int getWidth();
	int getHeight();
	
	int getX();
	int getY();
	int setX(int x);
	int setY(int y);
	
	bool isKeyPressed(int key);
	
	void setTitle(string title);
	string getTitle();

	ofWindowEvents events;
	
	static int lastWindowID;

	int mouseX, mouseY;
	int oldMouseX, oldMouseY;

private:
	GLFWwindow getGlfwWindow();
	
	void destroy();

	void mouseMoved(int mouseX, int mouseY);
	void mouseDragged(int mouseX, int mouseY, int button);
	void mousePressed(int button);
	void mousePressed(int mouseX, int mouseY, int button);
	void mouseReleased(int button);
	void mouseReleased(int mouseX, int mouseY, int button);

	void keyPressed(int key);
	void keyReleased(int key);
	
	void scrolled(float deltaX, float deltaY);

	void windowMoved(int x, int y);
	void windowFocused();
	void windowUnfocused();
	void windowClosed();
	void windowResized(int w, int h);
	
	
	ofWindowListenerList listeners;
	ofRectangle previousShape;
	bool isFocused;
	string title;
	GLFWwindow window;
	
	bool isInitialized;
	int id;

	bool keyState[OF_MAX_NUM_KEYS];
	
	friend class ofWindowManager;
};
