#include "../include/ofApp.h"
#include <thread>

using namespace patapon;

void PataponGame::setup() {
    ofSetWindowTitle("Patapon");
    ofBackground(ofColor::red);

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("TrimmedMetronome.wav");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);
    //music_player_.load();

    std::thread t(&PataponGame::playRhythm, this);
    t.detach();
    }

void PataponGame::playRhythm() {
    while(true) {
        if (current_state_ == GameState::IN_PROGRESS && (!beat_player_.isPlaying())) {
            beat_player_.play();
            last_beat_time_ = ofGetElapsedTimef();

        } else if (current_state_ == GameState::FINISHED) {
            break;
        }
    }
}

void PataponGame::update() {
    // if (should_update_) {
    //     if (current_state_ == GameState::IN_PROGRESS) {
    //         draw();
    //     }
    // }

    if (current_state_ == GameState::IN_PROGRESS) {
        draw();
    }
}

void PataponGame::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray, OF_GRADIENT_LINEAR);
    if (current_state_ == GameState::IN_PROGRESS) {
        if (ofGetElapsedTimef() - time_since_keypress_ <= 0.35f) {
            drawDrumName();
        }

        if (ofGetElapsedTimef() - last_beat_time_  <= 0.35f) {
            drawBeatBorder();
        }

    } else if (current_state_ == GameState::FINISHED) {
        drawFinished();
    }
}

void PataponGame::drawDrumName() {
    ofSetColor(0, 0, 0);

    switch (drum_played_) {
        case OF_KEY_UP:
            font_.drawString("CHAKA", ofGetWindowWidth() / 2, ofGetWindowHeight() / 4);
            break;

        case OF_KEY_RIGHT:
            font_.drawString("PON", 3 * ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);
            break;

        case OF_KEY_LEFT:
            font_.drawString("PATA", ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);
            break;

        case OF_KEY_DOWN:
            font_.drawString("DON", ofGetWindowWidth() / 2, 3 * ofGetWindowHeight() / 4);
            break;
    }
}

void PataponGame::drawFinished() {
    ofSetColor(ofColor::black);
    
    font_.drawString("You lost :(", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void PataponGame::drawBeatBorder() {
    ofSetColor(ofColor::black);
    ofNoFill();
    ofDrawRectangle(ofGetWindowWidth() / 45, ofGetWindowHeight() / 30, ofGetWindowWidth() - (2*ofGetWindowWidth()/45), ofGetWindowHeight() - (2*ofGetWindowHeight()/30));
    ofDrawRectangle(ofGetWindowWidth() / 40, ofGetWindowHeight() / 25, ofGetWindowWidth() - (2*ofGetWindowWidth()/40), ofGetWindowHeight() - (2*ofGetWindowHeight()/25));
}

double PataponGame::calculateTempoDiff() {
    double temp = time_since_keypress_ - last_beat_time_;
    std::cout << temp << std::endl;

    return temp;
}

void PataponGame::keyPressed(const int key) {

    if (std::find(valid_keys_.begin(), valid_keys_.end(), key) != valid_keys_.end()) {
        drum_played_ = key;
        should_update_ = false;
        time_since_keypress_ = ofGetElapsedTimef();
        tempoDiff_ = calculateTempoDiff();
        update();
    }

    return;
}

