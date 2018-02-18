#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

#include "ofxGraph.h"
#include "ofxGui.h"
#define _USE_MATH_DEFINES
#include <math.h>
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		float 	angle;
		bool	bSmooth;

		double drum_scale;
		double drum_x;
		double drum_y;
		double drum_x_zero;
		double drum_y_zero;

		double drum_angle;


		ofxGraph graph1;
		ofxGraph graph2;
		ofxGraph graph3;
		ofxGraph graph4;
		ofxPanel gui;
		ofxFloatSlider p01, p02, p03;
		ofxFloatSlider p04, p05, p06;
		ofxFloatSlider p07, p08, p09;
		ofxFloatSlider p10, p11, p12;

		ofParameter<bool>	doFullScreen;
		void				setFullScreen(bool& _value) { ofSetFullscreen(_value); }
		ofParameter<bool> bHide;
		ofParameter<string> screenSize;

		int scene_flg;

		double startTime;

		ofxTrueTypeFontUC font;
		double currentTime;

};
