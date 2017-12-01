#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(255);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();

	this->icoSphere.setRadius(300);
	this->icoSphere.setResolution(4);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	vector<ofMeshFace> triangles = this->icoSphere.getMesh().getUniqueFaces();

	for (int i = 0; i < triangles.size(); i++) {

		ofVec3f avg = (triangles[i].getVertex(0) + triangles[i].getVertex(1) + triangles[i].getVertex(2)) / 3;
		float noise_value = ofNoise(avg.x * 0.005, avg.y * 0.005 + ofGetFrameNum() * 0.005, avg.z * 0.005);

		ofMesh mesh;

		if (noise_value > 0.75) {

			mesh.addVertex(triangles[i].getVertex(0) * ofMap(noise_value, 0.75, 1, 1, 2));
			mesh.addVertex(triangles[i].getVertex(1) * ofMap(noise_value, 0.75, 1, 1, 2));
			mesh.addVertex(triangles[i].getVertex(2) * ofMap(noise_value, 0.75, 1, 1, 2));

			mesh.addVertex(triangles[i].getVertex(0));
			mesh.addVertex(triangles[i].getVertex(1));
			mesh.addVertex(triangles[i].getVertex(2));

			mesh.addIndex(0);
			mesh.addIndex(1);
			mesh.addIndex(2);

			mesh.addIndex(3);
			mesh.addIndex(4);
			mesh.addIndex(5);

			mesh.addIndex(0);
			mesh.addIndex(3);
			mesh.addIndex(4);

			mesh.addIndex(0);
			mesh.addIndex(1);
			mesh.addIndex(4);

			mesh.addIndex(1);
			mesh.addIndex(2);
			mesh.addIndex(4);

			mesh.addIndex(2);
			mesh.addIndex(5);
			mesh.addIndex(4);

			mesh.addIndex(0);
			mesh.addIndex(2);
			mesh.addIndex(3);

			mesh.addIndex(2);
			mesh.addIndex(3);
			mesh.addIndex(5);

			ofSetColor(255 - 255 * (noise_value - 0.75), 0, 0);
		} else {

			mesh.addVertex(triangles[i].getVertex(0));
			mesh.addVertex(triangles[i].getVertex(1));
			mesh.addVertex(triangles[i].getVertex(2));

			mesh.addIndex(0);
			mesh.addIndex(1);
			mesh.addIndex(2);

			ofSetColor(255, 0, 0);
		}

		mesh.draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}