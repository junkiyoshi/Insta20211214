#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	ofColor color;
	int color_count = 12;
	for (int i = 0; i < color_count; i++) {

		color.setHsb(ofMap(i, 0, color_count, 0, 255), 150, 200);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int radius = 540;
	int span = 30;

	for (int i = 0; i < this->color_list.size(); i++) {

		int deg_start = i % 3;
		for (int deg = deg_start; deg < deg_start + 360; deg += 3) {

			auto tmp_radius = (int)(ofRandom(radius)  + ofGetFrameNum() * 2) % radius;

			this->mesh.addVertex(glm::vec3(tmp_radius * cos(deg * DEG_TO_RAD), tmp_radius * sin(deg * DEG_TO_RAD), 0));
			this->mesh.addColor(ofColor(this->color_list[i], 0));
		}
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			auto distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < span) {

				auto alpha = distance < span * 0.25 ? 255 : ofMap(distance, span * 0.25, span, 255, 0);

				if (this->mesh.getColor(i).a < alpha) {

					this->mesh.setColor(i, ofColor(this->mesh.getColor(i), alpha));
				}

				if (this->mesh.getColor(k).a < alpha) {

					this->mesh.setColor(k, ofColor(this->mesh.getColor(k), alpha));
				}

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	this->mesh.drawWireframe();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawCircle(this->mesh.getVertex(i), 1.85);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}