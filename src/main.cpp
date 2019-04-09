#include "ofMain.h"
#include "../include/ofApp.h"

#define DISPLAY_MODE OF_WINDOW

int main() {
    ofSetupOpenGL(2560, 1440, DISPLAY_MODE);
    ofSetFrameRate(60);

    ofRunApp(new patapon::PataponGame());
}
