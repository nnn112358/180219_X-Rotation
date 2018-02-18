#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetCircleResolution(128);
	ofBackground(255, 255, 255);
	ofSetWindowTitle("drum roration");
	bSmooth = false;
	ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

	drum_scale = 1.3;
	drum_x_zero = 300;
	drum_y_zero = 300;
	drum_angle = 0.0;
	drum_x = 00.0;
	drum_y = 00.0;

	ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);

	graph1.setup(100, 100, 400, 400);
	graph1.setName("sensor1 wave X-Y");     // it automatically loads setting file, (sample.xml)
	graph1.setDx(1.0); // which means delta of time
	graph1.setColor(ofColor::black);
	graph1.setBufSize(1000);
	graph1.setLabel({ "x","y" });

	graph2.setup(300, 100, 400, 400);
	graph2.setName("sensor2 wave X-Y");     // it automatically loads setting file, (sample.xml)
	graph2.setDx(1.0); // which means delta of time
	graph2.setColor(ofColor::black);
	graph2.setBufSize(1000);
	graph2.setLabel({ "x","y" });

	graph3.setup(400, 100, 400, 400);
	graph3.setName("calcuration wave X-Y");     // it automatically loads setting file, (sample.xml)
	graph3.setDx(1.0); // which means delta of time
	graph3.setColor(ofColor::black);
	graph3.setBufSize(1000);
	graph3.setLabel({ "x","y" });

	graph4.setup(500, 100, 400, 400);
	graph4.setName("calcuration wave r-theta");     // it automatically loads setting file, (sample.xml)
	graph4.setDx(1.0); // which means delta of time
	graph4.setColor(ofColor::black);
	graph4.setBufSize(1000);
	graph4.setLabel({ "r","theta" });

	gui.setup("parametor");
	gui.add(screenSize.set("screenSize", ""));
	gui.add(bHide.set("GuiHide(h)", false));
	gui.add(doFullScreen.set("fullscreen (F)", false));
	gui.add(p01.setup("drum_scale", 1.3, 0.10, 5.0));
	gui.add(p02.setup("drum_x_zero", 200, 0.0, 1000.0));
	gui.add(p03.setup("drum_y_zero", 200, 0.0, 1000.0));
	
	gui.add(p04.setup("xx_amp", 1, 0.0, 20));
	gui.add(p05.setup("yy_amp", 1, 0.0, 20));
	gui.add(p06.setup("vel_amp", 1, 0.0, 20));
	gui.add(p07.setup("drum_speed", 1, 0.1, 10));

	gui.add(p08.setup("xx_freq", 30, 1.0, 50));
	gui.add(p09.setup("yy_freq", 20, 1.0, 50));
	gui.add(p10.setup("vel_freq", 25, 1.0, 50));
	gui.add(p11.setup("timer", 10.0, 10.0, 60));
	gui.add(p12.setup("Font Size", 50.0, 10, 100.0));

	doFullScreen.addListener(this, &ofApp::setFullScreen);
	gui.loadFromFile("settings.xml");

	drum_scale = p01;
	drum_x_zero = p02;
	drum_y_zero = p03;

	scene_flg = 0;
	
	startTime = ofGetElapsedTimef();
	font.loadFont("GenShinGothic-Bold.ttf", p12);

	currentTime = ofGetElapsedTimef() - startTime;
}

//--------------------------------------------------------------
void ofApp::update() {

	 currentTime = ofGetElapsedTimef() - startTime;
	if (currentTime > p11) {
		scene_flg++;
		startTime = ofGetElapsedTimef();
		if (scene_flg > 4)scene_flg = 0;

	}

	drum_scale = p01;
	drum_x_zero = p02;
	drum_y_zero = p03;

	double xx_amp = p04;
	double yy_amp = p05;
	double v_amp = p06;

	

	if (scene_flg == 1) {
		xx_amp = p04;
		yy_amp = 0;
		v_amp = 0.0;
	}
	else if (scene_flg == 2) {
		xx_amp = 0;
		yy_amp = p05;
		v_amp = 0;
	}
	else if (scene_flg == 3) {
		xx_amp = 0;
		yy_amp = 0;
		v_amp = p06;
	}
	else if (scene_flg == 4) {
		xx_amp = p04;
		yy_amp = p05;
		v_amp = 0;
	}
	else if (scene_flg == 0) {
		xx_amp = p04;
		yy_amp = p05;
		v_amp = p06;
	}

	drum_angle = drum_angle + p07;
	angle = angle + p07;

	double x_d = xx_amp*sin(angle * p08 / 180.0*M_PI);
	double y_d = yy_amp*sin(angle * p09 / 180.0*M_PI);
	double vel_d = v_amp*sin(angle * p10 / 180.0*M_PI);
	double vel_rd = v_amp*sin((angle) * p10 / 180.0*M_PI + M_PI / 2.0) / 5.0;

	drum_angle += vel_d;

	drum_x = drum_x_zero + x_d;
	drum_y = drum_y_zero + y_d;




	vector<float>value1;
	value1.push_back(-9.8*cos(angle / 180.0*M_PI) + x_d*sin(angle / 180.0*M_PI + M_PI / 2.0) + y_d*cos(angle / 180.0*M_PI) + vel_d);
	value1.push_back(-9.8*sin(angle / 180.0*M_PI) + x_d*sin(angle / 180.0*M_PI) + y_d*cos(angle / 180.0*M_PI+ M_PI/2.0) + vel_d / 5.0);

	graph1.add(value1);
	vector<float>value2;
	value2.push_back(-9.8*cos((angle + 180.0) / 180.0*M_PI) + y_d*cos((angle + 180.0) / 180.0*M_PI) +x_d*sin(angle / 180.0*M_PI +3.0* M_PI / 2.0) + vel_d);
	value2.push_back(-9.8*sin((angle + 180.0) / 180.0*M_PI) + x_d*sin((angle + 180.0) / 180.0*M_PI) + y_d*cos(angle / 180.0*M_PI + 3.0*M_PI / 2.0) + vel_d / 5.0);
	graph2.add(value2);

	vector<float>value3;
	value3.push_back(x_d);
	value3.push_back(y_d);
	graph3.add(value3);
	vector<float>value4;
	value4.push_back(vel_d);
	value4.push_back(vel_rd);
	graph4.add(value4);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(250, 250, 250);

	ofSetColor(0);


	ofSetColor(ofColor::darkCyan);
	ofFill();
	ofRect(0 , ofGetHeight()-25, (1.0 - currentTime / p11)*ofGetWidth(),25);
	



	if (!bHide) {
		gui.draw();
	}

	//let's draw a circle:
	ofSetLineWidth(1);
	ofSetColor(255);

	graph1.draw();
	graph2.draw();
	graph3.draw();
	graph4.draw();

	ofSetLineWidth(10);


	ofPushMatrix();
	ofSetColor(128, 128, 128);
	ofTranslate(drum_x, drum_y);

	ofRotateZ(drum_angle);
	ofFill();
	ofSetColor(ofColor::green);
	ofDrawCircle(0, 0, 100 * drum_scale);
	ofSetColor(255, 255, 255);
	ofDrawCircle(0, 0, 20 * drum_scale);
	ofSetColor(0, 0, 0);

	ofSetColor(0, 128, 255);
	ofRect(50 * drum_scale, -25 * drum_scale, 25 * drum_scale, 50 * drum_scale);
	ofRect(-50 * drum_scale, 25 * drum_scale, -25 * drum_scale, -50 * drum_scale);

	ofSetColor(0, 128, 0);
	ofNoFill();
	ofDrawCircle(0, 0, 100 * drum_scale);


	ofPopMatrix();

	ofPushMatrix();
	ofSetColor(128, 128, 128);
	ofTranslate(drum_x_zero, drum_y_zero);
	ofFill();
	ofDrawCircle(0, 0, 10 * drum_scale);
	ofPopMatrix();

	if (scene_flg == 1) {
		font.drawString("X•ûŒü-…•½•ûŒüU“®", 50, 50);
	}
	else if (scene_flg == 2) {
		font.drawString("Y•ûŒü-‚’¼•ûŒüU“®", 50, 50);
	}
	else if (scene_flg == 3) {
		font.drawString("ƒÆ•ûŒü-Žü•ûŒüU“®", 50, 50);
	}
	else if (scene_flg == 4) {
		font.drawString("X-Y•ûŒü …•½E‚’¼•ûŒüU“®", 50, 50);
	}
	else if (scene_flg == 0) {
		font.drawString("X-Y-ƒÆ•ûŒü …•½E‚’¼EŽü•ûŒüU“®", 50, 50);
	}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == 'h') {
		bHide = !bHide;
	}
	else if (key == 's') {
		gui.saveToFile("settings.xml");
	}
	else if (key == 'l') {
		gui.loadFromFile("settings.xml");
	}
	else if (key == 'f') {
		doFullScreen.set(!doFullScreen.get());
	}
	else if ((key == 13)|| (key == 32)) {
		scene_flg++;
		startTime = ofGetElapsedTimef();

		if (scene_flg > 4)scene_flg = 0;
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
